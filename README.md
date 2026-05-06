# Pokemon Gen 1 Save Reader
A C program that reads a Pokemon Gen 1 Save File.

### Features
- Reads Player Info (Name and TID) from a save file
- Reads `Box` Data Structure from a save file

### Endianness
The endianness of a Gen 1 save file is in Big Endian, so it is necessary to do byte swapping on multibyte data (assuming this program is being run on Windows, which is in Small Endian).

### Data Structures
**Trainer**
- `name` is the name of the trainer, found in address `0x2605`
- `id` is the ID of the trainer, found in address `0x2605`

**Box**
- `pokemon_count` counts the actual number of `Pokemon`s stored in a box
- `species_ids` contains the list of `Pokemon` species inside the box
- `padding` is an unused padding
- `pokemons` contains the list of `Pokemon` data structures
- `ot_names` contains the list of `Pokemon`s' original trainer name
- `pokemon_names` contains the list of `Pokemon`s' nicknames

The Current PC Box Number is stored in `0x284C`. Bits 0-6 stores the box number while the 7th bit indicates whether the trainer has switched boxes before. This data has a size of `0x2`, but only uses 8 bits. If a `Box` is the Current PC Box, then its data is stored in address `0x30C0` instead of Banks 2 (Stores Boxes 1-6) or 3 (Stores Boxes 7-12).

## Commit Conventions
The following commit conventions has been adopted from this [gist](https://gist.github.com/qoomon/5dfcdf8eec66a051ecd85625518cfd13).

    Changes relevant to the API or UI:
        <feat>: Commits that add, adjust or remove a new feature to the API or UI
        <fix>: Commits that fix an API or UI bug of a preceded <feat> commit
        
    <refactor>: Commits that rewrite or restructure code without altering API or UI behavior
        <perf>: Commits are special type of <refactor> commits that specifically improve performance

    <style>: Commits that address code style (e.g., white-space, formatting, missing semi-colons) and do not affect application behavior

    <test>: Commits that add missing tests or correct existing ones
    <docs>: Commits that exclusively affect documentation

    <build>: Commits that affect build-related components such as build tools, dependencies, project version, CI/CD pipelines, ...

    <ops>: Commits that affect operational components like infrastructure, deployment, backup, recovery procedures, ...

    <chore>: Commits that represent tasks like initial commit, modifying .gitignore, ...

## Prerequisites
In order to be able to compile and build this program, you need to install `gcc` compiler and `make` build tool

## Make commands
- `make all` compiles and builds the project into an `exe`
- `make clean` clears all `obj` files and the `exe`
- `make rebuild` automatically cleans and builds the project

## References
- https://bulbapedia.bulbagarden.net/wiki/Save_data_structure_(Generation_I)
- https://bulbapedia.bulbagarden.net/wiki/Pok%C3%A9mon_data_structure_(Generation_I)
- https://bulbapedia.bulbagarden.net/wiki/Stat
- https://github.com/kwsch/PKHeX/blob/master/PKHeX.Core/Saves/Substructures/Gen12/SAV1Offsets.cs