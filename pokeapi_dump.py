import requests
import os
import io
import json
from PIL import Image

from pprint import pprint

pokeapi_url = "http://localhost:8000/api/v2"
out_folder = "data"

pkm_list = []

def get_name(pkm_species):
    names = pkm_species['names']
    for name in names:
        if name['language']['name'] == 'en': return name['name']

    return ""

def get_stats(pkm):
    pkm_stats = pkm['stats']
    stats = {}
    for stat in pkm_stats:
        stats[stat['stat']['name']] = stat['base_stat']
    
    return stats

def get_types(pkm):
    pkm_types = pkm['types']
    types = []
    for t in pkm_types:
        types.append(t['type']['name'])

    return types

def get_genus(pkm_specie):
    pkm_genera = pkm_specie['genera']

    for genus in pkm_genera:
        if genus['language']['name'] == 'en': return genus['genus']

    return ""

def get_desc(pkm_specie):
    pkm_descs = pkm_specie['flavor_text_entries']

    for i in range(len(pkm_descs)-1, -1, -1):
        if pkm_descs[i]['language']['name'] == 'en': return pkm_descs[i]['flavor_text'].replace('\n', ' ')

    return ""

def save_sprite(pkm, filename):
    sprites = pkm['sprites']
    if sprites['front_default']:
        r = requests.get(sprites['front_default'])
        if r.status_code == 200:
            sprite_content = r.content
        else: 
            print("Could not find sprite")
            return
    else:
        print('Could not find sprite')
        return
    f = io.BytesIO(sprite_content)

    with Image.open(f) as sprite:
        width, height = sprite.size
        resized_dimensions = (int(width * 2), int(height * 2))
        resized = sprite.resize(resized_dimensions)
        resized.save(filename, "PNG")
    """ sprite = Image.open(f)

    with open(filename, 'wb') as s:
        sprite.save(s, "PNG") """

if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser(description="Pokeapi file dumping")
    parser.add_argument("-c", "--copy", help="Copy binaries from Downloads folder", action="store_true")
    parser.add_argument("-d", "--dump", help="Dump data from pokeapi", action="store_true")

    args = parser.parse_args()

    if args.dump:

        r = requests.get(f"{pokeapi_url}/pokedex/1/")

        if r.status_code == 200:
            national_dex = r.json()['pokemon_entries']
        else:
            print("Could not connect to the api.")
            exit(1)
        
        n_pkm = len(national_dex)

        print(f'Found {n_pkm} Pokémon entries in the national dex.')

        for entry in national_dex[:]:
            r = requests.get(entry['pokemon_species']['url'])

            if r.status_code == 200:
                pkm_specie = r.json()

            else:
                print(f"Entry {entry['entry_number']} not found!")
                continue

            r = requests.get(entry['pokemon_species']['url'].replace('pokemon-species', 'pokemon'))

            if r.status_code == 200:
                pkm = r.json()

            else:
                print(f"Entry {entry['entry_number']} not found!")
                continue

            name = get_name(pkm_specie)
            if ':' in name:
                name.replace(':', '_')
            if '♂' in name:
                name = 'Nidoran male'
            elif '♀' in name:
                name = 'Nidoran female'
            if '\u2019' in name:
                name = name.replace('\u2019', "\'")
            stats = get_stats(pkm)
            types = get_types(pkm)
            genus = get_genus(pkm_specie)
            desc = get_desc(pkm_specie)
            if '\u2014' in desc:
                print(desc)
                desc = desc.replace('\u2014', ' -')
            if '\u2019' in desc:
                print(desc)
                desc = desc.replace('\u2019', "\'")
            if '\u201c' in desc:
                print(desc)
                desc = desc.replace('\u201c', "\"")
            if '\u201d' in desc:
                print(desc)
                desc = desc.replace('\u201d', "\"")
            if '\u2212' in desc:
                print(desc)
                desc = desc.replace('\u2212', "-")

            print(f"Creating entry for pokemon {entry['entry_number']} {name}")

            pkm_entry = {
                "number": int(entry['entry_number']),
                "name": name,
                **stats,
                "types": types,
                "height": int(pkm['height']),
                "weight": int(pkm['weight']),
                "genus": genus,
                "desc": desc,
            }

            if not os.path.exists(f"{out_folder}/pkm_entries"): os.mkdir(f"{out_folder}/pkm_entries")
            if not os.path.exists(f"{out_folder}/sprites"): os.mkdir(f"{out_folder}/sprites")

            with open(f"{out_folder}/pkm_entries/{pkm_entry['number']:04d}-{pkm_entry['name'].replace(':', '_')}.json", 'w') as f:
                json.dump(pkm_entry, f)

            print(f"Creating sprite for pokemon {entry['entry_number']} {name}")

            save_sprite(pkm, f"{out_folder}/sprites/{pkm_entry['number']:04d}-{pkm_entry['name'].replace(':', '_')}.png")
        
            pkm_list.append(f"{pkm_entry['number']:04d}-{pkm_entry['name']}")
        with open("data/pkm_list.json", 'w') as f:
            json.dump(pkm_list, f)

    if args.copy:
        with open("data/pkm_list.json", 'r') as f:
            pkm_list = json.load(f)
        
        for p in pkm_list:
            os.system(f'mv /Users/kevimota/Downloads/"{p}.bin" data/sprites/.')