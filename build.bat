@REM rebuild the project
make rebuild

@REM fetch Pokemon data CSV if it doesn't exist yet
IF NOT EXIST "pkmn1.csv" (
    python pokemon_scraper.py
)

@REM run the program
make run