package me.commandcraft.chestbank.bank;

import org.bukkit.Bukkit;
import org.bukkit.Location;

public class Loc {

	private String worldName;
	private int x, y, z;

	protected Loc(Location loc) {
		this.worldName = loc.getWorld().getName();
		this.x = loc.getBlockX();
		this.y = loc.getBlockY();
		this.z = loc.getBlockZ();
	}

	public boolean equals(Location loc) {
		return (loc.getWorld().getName().equals(worldName) && loc.getBlockX() == x && loc.getBlockY() == y
				&& loc.getBlockZ() == z);
	}

	public Location getLocation() {
		return new Location(Bukkit.getWorld(worldName), x, y, z);
	}

	public String getWorldName() {
		return worldName;
	}

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}

	public int getZ() {
		return z;
	}

}
