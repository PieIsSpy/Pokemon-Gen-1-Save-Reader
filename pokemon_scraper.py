import requests
import pandas as pd
from bs4 import BeautifulSoup

url_stats = "https://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_base_stats_in_Generation_I"
url_index = "https://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_index_number_in_Generation_I"
url_growth = "https://pokestats.gg/growth-rates"

target_div = "MuiPaper-root MuiPaper-elevation MuiPaper-rounded MuiPaper-elevation1 MuiStack-root mui-16c1od"
target_a = "MuiButtonBase-root MuiChip-root MuiChip-outlined MuiChip-sizeMedium MuiChip-colorDefault MuiChip-clickable mui-1332fid"
target_h3 = "MuiTypography-root MuiTypography-sectionSubTitle mui-91jvpp"

header = {
  "User-Agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.75 Safari/537.36",
  "X-Requested-With": "XMLHttpRequest"
}

# request for the pages
req1 = requests.get(url_stats, headers=header)
req2 = requests.get(url_index, headers=header)
req3 = requests.get(url_growth, headers=header)

# get the table for pokemon gen 1 indices
df_index = pd.read_html(req2.text)[0]
df_index.columns = df_index.columns.get_level_values(1)
df_index = df_index.drop(columns=["HEX", "MS"])
df_index = df_index.rename(columns={"Name": "Pokemon"})
df_index['Pokemon'] = df_index['Pokemon'].str.replace('Nidoran♂', 'NidoranM')
df_index['Pokemon'] = df_index['Pokemon'].str.replace('Nidoran♀', 'NidoranF')

# get the table for pokemon base stats
df_stats = pd.read_html(req1.text)[1]
df_stats['Pokémon'] = df_stats["Pokémon.1"]
df_stats = df_stats.rename(columns={"Pokémon": "Pokemon"})
df_stats = df_stats.drop(columns=["Pokémon.1", "Total", "Average"])
df_stats['Pokemon'] = df_stats['Pokemon'].str.replace('Nidoran♂', 'NidoranM')
df_stats['Pokemon'] = df_stats['Pokemon'].str.replace('Nidoran♀', 'NidoranF')

# get the growth rate classification of each pokemon
df_growth = pd.DataFrame(columns=["Pokemon", "GrowthRate"])
soup = BeautifulSoup(req3.text, "html.parser")
growth_classifications = soup.find_all("div", {"class": target_div})

# for each growth rate type, fetch all the pokemons under it
for growth in growth_classifications:
    heading = growth.find("h3", {"class": target_h3})
    pokemon = growth.find_all("a", {"class": target_a})
    for pkmn in pokemon:
        df_growth.loc[len(df_growth)] = [pkmn.text, heading.text]

df_growth['GrowthRate'] = df_growth["GrowthRate"].str.replace(' ', '')
df_growth['Pokemon'] = df_growth['Pokemon'].str.replace('Nidoran F', 'NidoranF')
df_growth['Pokemon'] = df_growth['Pokemon'].str.replace('Nidoran M', 'NidoranM')
df_growth['Pokemon'] = df_growth['Pokemon'].str.replace('Mr Mime', 'Mr. Mime')

# combine all tables
df = pd.merge(df_stats, df_index, on='Pokemon')
df = pd.merge(df, df_growth, on='Pokemon')
df = df.rename(columns={"#": "DexNum", "Types": "Type1", "Types.1": "Type2"})
df = df.loc[:, ["DEC", "DexNum", "Pokemon", "GrowthRate", "Type1", "Type2", "HP",  "Attack",  "Defense",  "Speed",  "Special"]]
df = df.set_index("DEC")
df = df.sort_values(by=["DEC"])

df.to_csv('pkmn1.csv')