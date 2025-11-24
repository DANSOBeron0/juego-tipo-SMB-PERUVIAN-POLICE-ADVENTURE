from PIL import Image, ImageDraw

# Create a 32x64 pixel police officer sprite
img = Image.new('RGBA', (32, 64), (255, 255, 255, 0))
draw = ImageDraw.Draw(img)

# Police hat (dark blue)
draw.rectangle([8, 0, 24, 6], fill=(0, 0, 100))
draw.rectangle([6, 6, 26, 10], fill=(0, 0, 150))

# Head (skin tone)
draw.rectangle([10, 10, 22, 18], fill=(255, 220, 177))

# Eyes
draw.rectangle([12, 13, 14, 15], fill=(0, 0, 0))
draw.rectangle([18, 13, 20, 15], fill=(0, 0, 0))

# Police uniform - upper body (dark blue)
draw.rectangle([8, 18, 24, 38], fill=(0, 50, 150))

# Badge (yellow/gold)
draw.rectangle([14, 22, 18, 26], fill=(255, 215, 0))

# Arms
draw.rectangle([6, 20, 8, 36], fill=(0, 50, 150))  # Left arm
draw.rectangle([24, 20, 26, 36], fill=(0, 50, 150))  # Right arm

# Gun in right hand (dark gray)
draw.rectangle([26, 28, 30, 32], fill=(60, 60, 60))

# Belt (black)
draw.rectangle([8, 38, 24, 42], fill=(20, 20, 20))

# Pants (dark blue)
draw.rectangle([8, 42, 24, 64], fill=(0, 30, 100))

# Legs split
draw.rectangle([8, 42, 15, 64], fill=(0, 30, 100))  # Left leg
draw.rectangle([17, 42, 24, 64], fill=(0, 30, 100))  # Right leg

# Shoes (black)
draw.rectangle([8, 60, 15, 64], fill=(0, 0, 0))
draw.rectangle([17, 60, 24, 64], fill=(0, 0, 0))

# Save
img.save('assets/police_raw.png')
print("Created police_raw.png")
