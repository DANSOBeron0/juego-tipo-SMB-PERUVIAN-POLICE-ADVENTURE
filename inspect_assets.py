from PIL import Image
import os

assets_dir = r"c:/Users/clevernet/proyectos c++/graficos/assets"
files = ["alan_garcia.png", "tiles.png"]

for f in files:
    path = os.path.join(assets_dir, f)
    if os.path.exists(path):
        try:
            img = Image.open(path)
            print(f"File: {f}")
            print(f"  Size: {img.size}")
            print(f"  Mode: {img.mode}")
            bbox = img.getbbox()
            print(f"  Content BBox: {bbox}")
        except Exception as e:
            print(f"  Error opening {f}: {e}")
    else:
        print(f"File not found: {path}")
