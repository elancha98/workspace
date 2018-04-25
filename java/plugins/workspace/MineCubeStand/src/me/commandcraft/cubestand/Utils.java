package me.commandcraft.cubestand;

import java.util.ArrayList;
import java.util.List;

import org.bukkit.Location;
import org.bukkit.entity.ArmorStand;
import org.bukkit.entity.Entity;
import org.bukkit.entity.Player;
import org.bukkit.util.BlockIterator;

public class Utils {
	
	public static final int MAX_DISTANCE = 7;

	public static ArmorStand getArmorStand(Player p) {
		List<ArmorStand> armorStands = getNearbyArmorstands(p);
		BlockIterator iterator = new BlockIterator(p, MAX_DISTANCE);
		while (iterator.hasNext()) {
			Location block = iterator.next().getLocation();
			for (ArmorStand a : armorStands) {
				if (a.getLocation().distance(block) <= 1) return a;
			}
		}
		return null;
	}
	
	public static List<ArmorStand> getNearbyArmorstands(Player p) {
		List<Entity> entities = p.getNearbyEntities(MAX_DISTANCE, MAX_DISTANCE, MAX_DISTANCE);
		List<ArmorStand> armorStands = new ArrayList<ArmorStand>();
		for (Entity e : entities) {
			if (e instanceof ArmorStand) armorStands.add((ArmorStand) e);
		}
		return armorStands;
	}
}
