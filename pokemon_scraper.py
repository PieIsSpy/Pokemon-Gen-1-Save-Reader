import requests
import pandas as pd

url_stats = "https://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_base_stats_in_Generation_I"
url_index = "https://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_index_number_in_Generation_I"

header = {
  "User-Agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.75 Safari/537.36",
  "X-Requested-With": "XMLHttpRequest"
}

req1 = requests.get(url_stats, headers=header)
req2 = requests.get(url_index, headers=header)

df_index = pd.read_html(req2.text)[0]
df_index.columns = df_index.columns.get_level_values(1)
df_index = df_index.drop(columns=["HEX", "MS"])
df_index = df_index.rename(columns={"Name": "Pokémon"})

df_stats = pd.read_html(req1.text)[1]
df_stats['Pokémon'] = df_stats["Pokémon.1"]
df_stats = df_stats.drop(columns=["Pokémon.1", "Total", "Average"])

df = pd.merge(df_stats, df_index, on='Pokémon')
df = df.rename(columns={"#": "DexNum", "Types": "Type1", "Types.1": "Type2"})
df = df.loc[:, ["DEC", "DexNum", "Pokémon", "Type1", "Type2", "HP",  "Attack",  "Defense",  "Speed",  "Special"]]
df = df.set_index("DEC")
df = df.sort_values(by=["DEC"])
df.to_csv('pkmn1.csv')