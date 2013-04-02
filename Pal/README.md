Program for extracting palette color from file *.pal and create a ouput png file.

# File structure

Files must be of 768 bytes long.

It contains RGB values for 256 colors.

	struct rgbvalue
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};

# Example "combat.pal"

![combat.pal_palette.png][1]

[1]:img/combat.pal_palette.png
