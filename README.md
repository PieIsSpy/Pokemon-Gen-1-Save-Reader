# Pokemon Gen 1 Save Reader
This is a prototype that reads a Pokemon Gen 1 Save File and allows for depositing and withdrawing Pokemons.

**DISCLAIMER**: This repository does ***NOT*** contain any copy of any Pokemon games. Get your own copy.

**DISCLAIMER2**: This iteration is ***NOT*** final and is only for testing features. Back up your save file when using it with this program.

### Features
- Reads Player Info (Name and TID) from a save file
- Reads `Box` Data Structure from a save file
- Reads `BoxPokemon` Data Structure and calculates its derived values
- Withdraw a `BoxPokemon` from a `Box` and export it as `.pkmn1`
- Import a `.pkmn1` file and deposits it into a `Box`

### Assumption
This README is in the assumption that you are running this program in Windows 11, which is in Small Endian.

### Endianness
The Endianness of a Gen 1 save file is in Big Endian, so it is necessary to do byte swapping on multibyte data in order to reformat it into Small Endian.

### Data Structures
**Trainer**
- `name` is the name of the trainer, found in address `0x2605`
- `id` is the ID of the trainer, found in address `0x2605`

**Box**
- `pokemon_count` counts the actual number of `BoxPokemon`s stored in a box
- `species_ids` contains the list of `BoxPokemon` species inside the box
- `padding` is an unused padding
- `pokemons` contains the list of `BoxPokemon` data structures
- `ot_names` contains the list of `BoxPokemon`s' original trainer name
- `pokemon_names` contains the list of `BoxPokemon`s' nicknames

The Current PC Box Number is stored in `0x284C`. Bits 0-6 stores the box number while the 7th bit indicates whether the trainer has switched boxes before. This data has a size of `0x2`, but only uses 1 byte. If a `Box` is the Current PC Box, then its data is stored in address `0x30C0` instead of Banks 2 (Stores Boxes 1-6) or 3 (Stores Boxes 7-12).

To retain data integrity, names are only converted to ASCII if and only if it has to be displayed.

**Box Pokemon**
- `speciesId` is the index of the `BoxPokemon`'s species in Gen 1
- `curHP` is the current HP of the `BoxPokemon`
- `level` is the level of the `BoxPokemon`
- `status` is the status condition of the `BoxPokemon`
- `type1` and `type2` are the elemental types of the `BoxPokemon`
- `catchRate` is the catch rate of the `BoxPokemon`'s species during capture (does not change after evolving)
- `move1`, `move2`, `move3`, `move4` are the indices of the `BoxPokemon`'s moves
- `tid` the `BoxPokemon`'s OT ID number
- `exp` is the total experience points accumulated
- `hpEV`, `atkEV`, `defEV`, `spdEV`, `speEV` are the EVs of the `BoxPokemon`
- `ivs` are the IVs of the `BoxPokemon`
- `move1PP`, `move2PP`, `move3PP`, `move4PP` are the PP information of the `BoxPokemon`'s moves

To retain data integrity, multibyte fields of `BoxPokemon` will only be reformatted to Small Endian if and only if it has to be displayed.

The IVs of the `BoxPokemon` are stored as 2 bytes of unsigned int, with each nibble representing Attack (Most Significant Nibble), Defense, Speed and Special (Least Significant Nibble). The HP IV of the `BoxPokemon` is derived from getting all the least significant bits of all the nibbles of the IV storage in the same order it was arranged.

Since this program should not require a copy of the game, species index numbers, names, types and base stats were scraped from [bulbapedia](https://bulbapedia.bulbagarden.net/wiki/Main_Page).

The derived values are computed as follows:
```math
\text{HP} = \bigg \lfloor \frac{((\text{Base} + \text{IV}) \times 2 + \lfloor \frac{\sqrt{EV}}{4} \rfloor) \times \text{Level}}{100} \bigg \rfloor + \text{Level} + 10
```

```math
\text{OtherStats} = \bigg \lfloor \frac{((\text{Base} + \text{IV}) \times 2 + \lfloor \frac{\sqrt{EV}}{4} \rfloor) \times \text{Level}}{100} \bigg \rfloor + 5
```
Note: Square Roots are rounded up due to how assembly work.

### Checksum
Checksums are used to check if the save file is corrupted or tampered. Therefore, recalculating the necessary checksums of the save file after editing is necessary in order to ensure that the save file still valid.

The location and the amount of checksums to recalculate depends on whether the edited box is a current box or an inactive box:
- If the edited box is the current box of the save file, then its checksum resides in Bank 1 in `0x3523`
- If the edited box is from boxes 1 - 6, then its overall checksum resides in Bank 2 in `0x5A4C`, with each of its boxes having its checksums starting at `0x5A4D`.
- If the edited box is from boxes 7 - 12, then its overall checksum resides in Bank 3 in `0x7A4C`, with each of its boxes having its checksums starting at `0x7A4D`.

The general computation of a checksum is as follows:
- Initialize the checksum to 0 as 1 byte of unsigned int
- For each increment of the adddress from the starting address to the last address it occupies, inclusive, add its byte to the checksum
- Invert the resulting checksum's bits

Or in formula form:
```math
\text{Checksum} = \sum_{i = \text{a}}^{\text{b}} i,
```
where $a$ is the Starting Address, $b$ is the Ending Address and $i$ is the stored byte in that address.

Take note that because the checksum is a 1 byte unsigned int, the computation will only get the Least Significant Byte after computation. After computing for the summation, the resulting byte gets all of its bits inverted and stored in its respective checksum address.

For Bank 1, the Main Data Checksum covers from Player Name (`0x2598`) to Tileset Type (`0x3522`).

For Banks 2 or 3, in order to reduce the needed computation, we can choose to only compute for that particular box's checksum before computing for the bank's overall checksum. 

For example, if the edited box is Box 7, then its checksum would be in `0x7A54` which will compute from address `0x6000` to `0x6000` + (`0x462` - 1), where `0x462` is the size of the box. Note that the size was subtracted by 1 because the next byte after this is the starting address of Box 8. After computing for the checksum of Box 7, we can then recompute for the overall checksum, which is computed from `0x7A4D` to `0x7A4D` + (`0x6` - 1) and store it at `0x7A4C`.

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
In order to be able to compile and build this program, you need to install a `gcc` compiler and `make` build tool. Additionally, you will have to install a `python` interpreter and have pip installed `requests`, `pandas` and `BeautifulSoup` modules to generate `pkmn1.csv` for the main program to properly render Pokemon information.

## Make commands
- `make all` compiles and builds the project into an `exe`
- `make clean` clears all `obj` files and the `exe`
- `make rebuild` automatically cleans and builds the project

# Running the project
Run `build.bat` or run the following commands in the command line:
```
make rebuild
python pokemon_scraper.py
make run
```

## References
- https://bulbapedia.bulbagarden.net/wiki/Save_data_structure_(Generation_I)
- https://bulbapedia.bulbagarden.net/wiki/Pok%C3%A9mon_data_structure_(Generation_I)
- https://bulbapedia.bulbagarden.net/wiki/Stat
- https://github.com/kwsch/PKHeX/blob/master/PKHeX.Core/Saves/Substructures/Gen12/SAV1Offsets.cs
- https://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_base_stats_in_Generation_I
- https://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_index_number_in_Generation_I
- https://youtu.be/4WOPsz-KmYk
- https://bulbapedia.bulbagarden.net/wiki/Individual_values
- https://youtu.be/VVbRe7wr3G4