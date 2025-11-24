from PIL import Image, ImageDraw

# Create animation frames for police officer
# Layout: 4 frames x 64 height = 128x64 sprite sheet
# Frame 0: Idle
# Frame 1: Walk 1
# Frame 2: Walk 2
# Frame 3: Jump

img = Image.new('RGBA', (128, 64), (255, 255, 255, 0))

def draw_police_base(draw, x_offset, hat_y=0, body_y=18, leg_offset=0, arm_offset=0):
    """Draw base police officer parts"""
    # Police hat (dark blue)
    draw.rectangle([x_offset + 8, hat_y, x_offset + 24, hat_y + 6], fill=(0, 0, 100))
    draw.rectangle([x_offset + 6, hat_y + 6, x_offset + 26, hat_y + 10], fill=(0, 0, 150))
    
    # Head (skin tone)
    draw.rectangle([x_offset + 10, 10, x_offset + 22, 18], fill=(255, 220, 177))
    
    # Eyes
    draw.rectangle([x_offset + 12, 13, x_offset + 14, 15], fill=(0, 0, 0))
    draw.rectangle([x_offset + 18, 13, x_offset + 20, 15], fill=(0, 0, 0))
    
    # Police uniform - upper body (dark blue)
    draw.rectangle([x_offset + 8, body_y, x_offset + 24, 38], fill=(0, 50, 150))
    
    # Badge (yellow/gold)
    draw.rectangle([x_offset + 14, 22, x_offset + 18, 26], fill=(255, 215, 0))
    
    # Arms
    draw.rectangle([x_offset + 6, 20 + arm_offset, x_offset + 8, 36], fill=(0, 50, 150))  # Left arm
    draw.rectangle([x_offset + 24, 20 + arm_offset, x_offset + 26, 36], fill=(0, 50, 150))  # Right arm
    
    # Gun in right hand (dark gray)
    draw.rectangle([x_offset + 26, 28 + arm_offset, x_offset + 30, 32 + arm_offset], fill=(60, 60, 60))
    
    # Belt (black)
    draw.rectangle([x_offset + 8, 38, x_offset + 24, 42], fill=(20, 20, 20))
    
    # Pants (dark blue) - adjusted for leg offset
    draw.rectangle([x_offset + 8, 42, x_offset + 15, 64 - leg_offset], fill=(0, 30, 100))  # Left leg
    draw.rectangle([x_offset + 17, 42, x_offset + 24, 64], fill=(0, 30, 100))  # Right leg
    
    # Shoes (black)
    draw.rectangle([x_offset + 8, 60 - leg_offset, x_offset + 15, 64 - leg_offset], fill=(0, 0, 0))
    draw.rectangle([x_offset + 17, 60, x_offset + 24, 64], fill=(0, 0, 0))

draw = ImageDraw.Draw(img)

# Frame 0: Idle (standing still)
draw_police_base(draw, 0, 0, 18, 0, 0)

# Frame 1: Walk 1 (left leg forward)
draw_police_base(draw, 32, 0, 18, 2, 0)

# Frame 2: Walk 2 (right leg forward) 
draw_police_base(draw, 64, 0, 18, 0, 0)
# Adjust right leg for walking
draw.rectangle([64 + 17, 42, 64 + 24, 62], fill=(0, 30, 100))
draw.rectangle([64 + 17, 58, 64 + 24, 62], fill=(0, 0, 0))

# Frame 3: Jump (legs together, arms up slightly)
draw_police_base(draw, 96, 0, 18, 0, -2)
# Both legs together
draw.rectangle([96 + 10, 42, 96 + 22, 64], fill=(0, 30, 100))
draw.rectangle([96 + 10, 60, 96 + 22, 64], fill=(0, 0, 0))

img.save('assets/police_animations.png')
print("Created police_animations.png (128x64, 4 frames)")

# Create sword sprite
sword = Image.new('RGBA', (32, 32), (255, 255, 255, 0))
draw_sword = ImageDraw.Draw(sword)

# Sword blade (silver/gray)
draw_sword.rectangle([14, 4, 18, 24], fill=(192, 192, 192))
draw_sword.polygon([(14, 4), (16, 0), (18, 4)], fill=(192, 192, 192))  # Tip

# Sword guard (gold)
draw_sword.rectangle([10, 24, 22, 26], fill=(255, 215, 0))

# Sword handle (brown)
draw_sword.rectangle([14, 26, 18, 30], fill=(139, 69, 19))

# Pommel (gold)
draw_sword.ellipse([12, 30, 20, 32], fill=(255, 215, 0))

sword.save('assets/sword.png')
print("Created sword.png (32x32)")
