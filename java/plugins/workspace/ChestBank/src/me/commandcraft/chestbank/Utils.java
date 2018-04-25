package me.commandcraft.chestbank;

import java.io.StringReader;
import java.util.Set;

import org.bukkit.Location;
import org.bukkit.Material;
import org.bukkit.configuration.file.YamlConfiguration;
import org.bukkit.entity.HumanEntity;
import org.bukkit.entity.Player;
import org.bukkit.inventory.ItemStack;

public class Utils {

	private static YamlConfiguration configuration = new YamlConfiguration();
	
	public static String toString(ItemStack item) {
		configuration.set("item", item);
		return configuration.saveToString();
	}
	
	public static ItemStack fromString(String s) {
		configuration = YamlConfiguration.loadConfiguration(new StringReader(s));
		return configuration.getItemStack("item");
	}
	
	public static Location getTarget(HumanEntity p) {
		return p.getTargetBlock((Set<Material>)null, 0).getLocation();
	}
	
	public static boolean hasGroup(Player p, String group) {
		return ChestBank.getPermission().playerInGroup(p, group);
	}
}
