package me.commandcraft.showcase;

import org.bukkit.Bukkit;
import org.bukkit.inventory.ItemStack;

public class Utils {

	public static String getTellraw(String uuid, ItemStack is) {
		String s = "{\"text\":\"[Item]\",\"color\":\"dark_aqua\",\"bold\":true,\"clickEvent\":{\"action\":\"run_command\",\"value\":\"showcase ";
		s += uuid;
//		s += "\"},\"hoverEvent\":{\"action\":\"show_item\",\"value\":\"";
//		s += getTag(is).replaceAll("[\"]", "").replaceAll("[^\\[\\],:{}]+", "\\\\\"$0\\\\\"");;
		s += "\"}";
		return s;
	}
	
	private static String getTag(ItemStack is) {
		try {
			Object iStack = getCraftItemStack().getMethod("asNMSCopy", ItemStack.class).invoke(null, is);
			Object tag = getNBTTag().getConstructor().newInstance();
			getNMSItemStack().getMethod("save", getNBTTag()).invoke(iStack, tag);
			return tag.toString();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return "";
	}
	
	private static Class<?> getNBTTag() {
		try {
			return Class.forName("net.minecraft.server." + version() + ".NBTTagCompound");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	private static Class<?> getNMSItemStack() {
		try {
			return Class.forName("net.minecraft.server." + version() + ".ItemStack");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	private static Class<?> getCraftItemStack() {
		try {
			return Class.forName("org.bukkit.craftbukkit." + version() + ".inventory.CraftItemStack");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	private static String version() {
		String version  = Bukkit.getServer().getClass().getPackage().getName();
		return version.split("\\.")[3];
	}
}

//[{"text":"zorradelboske64","color":"green","bold":true},{"text":" is showcasing this ","color":"gold","bold":false},{"text":"[Item]","color":"dark_aqua","bold":true,"clickEvent":{"action":"run_command","value":"showcase 17db5f26-70d7-4ed8-bda5-457c192d941b"},"hoverEvent":{"action":"show_item","value":"{\"id\":\"minecraft\":\"log\",\"Count\":\"1b\",\"Damage\":\"2s\"}"}]