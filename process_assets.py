from PIL import Image, ImageDraw
import os

assets_dir = r"c:/Users/clevernet/proyectos c++/graficos/assets"
brain_dir = r"C:/Users/clevernet/.gemini/antigravity/brain/a2c61b70-9ab1-4250-8441-fbb979328eff"

def process_player():
    # Create a 32x64 sprite for full body (police officer)
    img = Image.new('RGBA', (32, 64), (0, 0, 0, 0))
    
    # Try to load the police sprite
    raw_path = os.path.join(assets_dir, "police_raw.png")
    if os.path.exists(raw_path):
        try:
            body = Image.open(raw_path).convert('RGBA')
            # Already 32x64, so just paste it
            img.paste(body, (0, 0))
        except Exception as e:
            print(f"Error processing raw player: {e}")
            # Fallback - blue body
            draw = ImageDraw.Draw(img)
            draw.rectangle([8, 16, 24, 64], fill='blue')
            draw.rectangle([8, 0, 24, 16], fill='navy')

    img.save(os.path.join(assets_dir, "alan_garcia.png"))
    print("Generated alan_garcia.png (32x64 police sprite)")

def process_tiles():
    # Create a tileset: 128x32
    # 0: Ground (Brown)
    # 1: Brick (Orange)
    # 2: Question (Gold)
    # 3: Pipe (Green)
    
    img = Image.new('RGBA', (128, 32), (0, 0, 0, 0))
    draw = ImageDraw.Draw(img)
    
    # Ground (0-32)
    draw.rectangle([0, 0, 32, 32], fill='#8B4513')
    draw.rectangle([0, 0, 32, 4], fill='#A0522D') # Grass top
    
    # Brick (32-64)
    # Try to load raw brick
    raw_path = os.path.join(assets_dir, "brick_raw.png")
    if os.path.exists(raw_path):
        try:
            brick = Image.open(raw_path).convert('RGBA')
            brick = brick.resize((32, 32), Image.Resampling.NEAREST)
            img.paste(brick, (32, 0))
        except:
            draw.rectangle([32, 0, 64, 32], fill='#CD853F')
            draw.rectangle([33, 1, 63, 31], outline='black')
    else:
        draw.rectangle([32, 0, 64, 32], fill='#CD853F')
        draw.rectangle([33, 1, 63, 31], outline='black')

    # Question (64-96)
    draw.rectangle([64, 0, 96, 32], fill='#FFD700')
    draw.text((74, 8), "?", fill='black') # Might need font, but simple rects work
    draw.rectangle([70, 5, 90, 27], outline='brown')

    # Pipe (96-128) - Not used yet but good to have
    draw.rectangle([96, 0, 128, 32], fill='#228B22')
    
    img.save(os.path.join(assets_dir, "tiles.png"))
    print("Generated tiles.png")

def process_backgrounds():
    # Background
    raw_bg = os.path.join(assets_dir, "lima_background_raw.png")
    if os.path.exists(raw_bg):
        try:
            bg = Image.open(raw_bg).convert('RGBA')
            bg = bg.resize((800, 450), Image.Resampling.BILINEAR) # Resize to screen size
            bg.save(os.path.join(assets_dir, "background.png"))
            print("Generated background.png")
        except Exception as e:
            print(f"Error processing background: {e}")

    # Landmarks (Palace, Bus, Train)
    raw_landmarks = os.path.join(assets_dir, "lima_landmarks_raw.png")
    if os.path.exists(raw_landmarks):
        try:
            lm = Image.open(raw_landmarks).convert('RGBA')
            
            # Make white transparent
            data = lm.getdata()
            new_data = []
            for item in data:
                # Change all white (also shades of whites) to transparent
                if item[0] > 240 and item[1] > 240 and item[2] > 240:
                    new_data.append((255, 255, 255, 0))
                else:
                    new_data.append(item)
            lm.putdata(new_data)
            
            lm.save(os.path.join(assets_dir, "landmarks.png"))
            print("Generated landmarks.png with transparency")
        except Exception as e:
            print(f"Error processing landmarks: {e}")

if __name__ == "__main__":
    process_player()
    process_tiles()
    process_backgrounds()
