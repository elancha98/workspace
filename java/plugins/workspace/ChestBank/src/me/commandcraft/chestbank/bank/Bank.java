package me.commandcraft.chestbank.bank;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.bukkit.Bukkit;
import org.bukkit.Location;
import org.bukkit.entity.Player;
import org.bukkit.event.Listener;
import org.bukkit.inventory.Inventory;
import org.bukkit.inventory.InventoryHolder;
import org.bukkit.inventory.ItemStack;

import me.commandcraft.chestbank.ChestBank;
import me.commandcraft.chestbank.Utils;


public class Bank implements Listener {
	
	private List<Loc> locs;
	private Map<String, String[]> items;
	private int rows;
	private String groupname;
	
	public Bank(String groupname, int rows) {
		this.groupname = groupname;
		this.rows = rows;
		this.locs = new ArrayList<Loc>();
		this.items = new HashMap<String, String[]>();
	}
	
	public void addLoc(Location loc) {
		locs.add(new Loc(loc));
	}
	
	public String getGroupname() {
		return groupname;
	}
	
	public boolean setRows(int rows) {
		if (rows < this.rows) return false;
		this.rows = rows;
		return true;
	}
	
	public boolean removeLocation(Location location) {
		for (int i = 0; i < locs.size(); i++) {
			if (locs.get(i).equals(location)) {
				locs.remove(i);
				return true;
			}
		}
		return false;
	}
	
	//Returns false if the location was not found
	public boolean hasLocation(Location location) {
		for (int i = 0; i < locs.size(); i++) {
			if (locs.get(i).equals(location)) return true;
		}
		return false;
	}
	
	public void saveContents(Inventory inv, Player p) {
		ItemStack[] contents = inv.getContents();
		String[] items = new String[contents.length];
		for (int i = 0; i < contents.length; i++) {
			items[i] = Utils.toString(contents[i]);
		}
		this.items.put(p.getName(), items);
	}
	
	public void openBank(int id, Player p) {
		Inventory inv = Bukkit.createInventory(new CCHolder(id), rows*9, ChestBank.getConfiguration().getTitle());
		String[] s = items.get(p.getName());
		if (s == null) s = new String[0];
		ItemStack[] contens = new ItemStack[s.length];
		for (int i = 0; i < contens.length; i++) {
			contens[i] = Utils.fromString(s[i]);
		}
		inv.setContents(contens);
		p.openInventory(inv);
	}
}

class CCHolder implements InventoryHolder {

	private int id;
	
	public CCHolder(int id) {
		this.id = id;
	}
	
	@Override
	public Inventory getInventory() {
		return null;
	}
	
	public int getId() {
		return id;
	}
}