package me.commandcraft.soulbound;

import java.util.ArrayList;
import java.util.List;

import org.bukkit.Bukkit;
import org.bukkit.ChatColor;
import org.bukkit.Material;
import org.bukkit.inventory.ItemStack;
import org.bukkit.inventory.meta.ItemMeta;


public class Utils {
	
	private static final String VERSION = Bukkit.getServer().getClass().getPackage().getName().split("\\.")[3];

	public static boolean isSoulbound(ItemStack is) {
		if (is == null || is.getType().equals(Material.AIR)) return false;
		try {
			Object item = getCraftItem().getMethod("asNMSCopy", ItemStack.class).invoke(null, is);
			Object nbt = item.getClass().getMethod("getTag").invoke(item);
			return (boolean) nbt.getClass().getMethod("hasKey", String.class).invoke(nbt, "soulbound");
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
	}
	
	public static String getSoulBound(ItemStack is) {
		try {
			Object item = getCraftItem().getMethod("asNMSCopy", ItemStack.class).invoke(null, is);
			Object nbt = item.getClass().getMethod("getTag").invoke(item);
			return (String) nbt.getClass().getMethod("getString", String.class).invoke(nbt, "soulbound");
		} catch (Exception e) {
			e.printStackTrace();
			return "";
		}
	}
	
	public static ItemStack setSoulBound(ItemStack is, String group) {
		try {
			Object nbt = getNBT().getConstructor().newInstance();
			nbt.getClass().getMethod("setString", String.class, String.class).invoke(nbt, "soulbound", group);
			Object item = getCraftItem().getMethod("asNMSCopy", ItemStack.class).invoke(null, is);
			item.getClass().getMethod("setTag", getNBT()).invoke(item, nbt);
			ItemStack ret =  (ItemStack) getCraftItem().getMethod("asBukkitCopy", item.getClass()).invoke(null, item);
			ItemMeta meta = ret.getItemMeta();
			List<String> lore = meta.getLore();
			if (lore == null) lore = new ArrayList<String>();
			lore.add(ChatColor.translateAlternateColorCodes('&', "&csoulbound: " + group));
			meta.setLore(lore);
			ret.setItemMeta(meta);
			return ret;
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
	}
	
	private static Class<?> getCraftItem() {
		try {
			return Class.forName("org.bukkit.craftbukkit." + VERSION + ".inventory.CraftItemStack");
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}
	
	private static Class<?> getNBT() {
		try {
			return Class.forName("net.minecraft.server." + VERSION + ".NBTTagCompound");
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}
}
