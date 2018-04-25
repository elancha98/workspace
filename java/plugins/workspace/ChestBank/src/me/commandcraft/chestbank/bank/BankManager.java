package me.commandcraft.chestbank.bank;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Reader;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.List;

import org.bukkit.ChatColor;
import org.bukkit.Location;
import org.bukkit.Material;
import org.bukkit.block.Block;
import org.bukkit.entity.Player;
import org.bukkit.event.EventHandler;
import org.bukkit.event.Listener;
import org.bukkit.event.block.BlockBreakEvent;
import org.bukkit.event.inventory.InventoryCloseEvent;
import org.bukkit.event.inventory.InventoryOpenEvent;
import org.bukkit.inventory.Inventory;

import com.google.common.reflect.TypeToken;
import com.google.gson.Gson;

import me.commandcraft.chestbank.ChestBank;
import me.commandcraft.chestbank.Utils;

public class BankManager implements Listener {

	private List<Bank> banks;
	
	public BankManager() throws IOException {
		load();
	}
	
	public boolean hasLocation(Location loc) {
		for (Bank bank : banks) {
			if (bank.hasLocation(loc)) return true;
		}
		return false;
	}
	
	public boolean hasBank(String groupname) {
		for (Bank bank : banks) {
			if (bank.getGroupname().equals(groupname)) return true;
		}
		return false;
	}
	
	public boolean setBank(String groupname, int rows) {
		for (Bank bank : banks) {
			if (bank.getGroupname().equals(groupname)) {
				return bank.setRows(rows);
			}
		}
		banks.add(new Bank(groupname, rows));
		return true;
	}
	
	public void addLocation(String groupname, Location loc) {
		for (Bank bank : banks) {
			if (bank.getGroupname().equals(groupname)) {
				bank.addLoc(loc);
				return;
			}
		}
	}

	@EventHandler
	public void onChestBroke(BlockBreakEvent event) {
		Block b = event.getBlock();
		if (b.getType().equals(Material.CHEST) || b.getType().equals(Material.TRAPPED_CHEST)) {
			Location location = b.getLocation();
			for (Bank bank : banks) {
				if (bank.removeLocation(location)) return;
			}
		}
	}
	
	@EventHandler
	public void onChestOpen(InventoryOpenEvent event) {
		if (event.getInventory().getHolder() instanceof CCHolder) return;
		Location location = Utils.getTarget(event.getPlayer());
		Player p = (Player) event.getPlayer();
		for (int i = 0; i < banks.size(); i++) {
			if (banks.get(i).hasLocation(location)) {
				event.setCancelled(true);
				if (Utils.hasGroup(p, banks.get(i).getGroupname())) banks.get(i).openBank(i, p);
				else p.sendMessage(ChatColor.RED + "You don't have permissions to open that bank");
				return;
			}
		}
	}

	@EventHandler
	public void onBankClose(InventoryCloseEvent event) {
		if (!(event.getPlayer() instanceof Player)) return;
		Inventory inventory = event.getInventory();
		if (inventory.getHolder() instanceof CCHolder) {
			int index = ((CCHolder) inventory.getHolder()).getId();
			banks.get(index).saveContents(inventory,
					(Player) event.getPlayer());
		}
	}

	@SuppressWarnings("serial")
	public void load() throws IOException {
		File file = new File(ChestBank.getInstance().getDataFolder(), "banks.json");
		try {
			Reader reader = new FileReader(file);
			Type type = new TypeToken<List<Bank>>() {}.getType();
			banks = new Gson().fromJson(reader, type);
		} catch (FileNotFoundException e) {
			banks = new ArrayList<Bank>();
		}
	}

	public void save() throws IOException {
		String saveString = new Gson().toJson(banks);
		File folder = ChestBank.getInstance().getDataFolder();
		folder.mkdirs();
		File file = new File(folder, "banks.json");
		if (!file.exists()) {
			file.createNewFile();
		}
		FileWriter writer = new FileWriter(file);
		writer.write(saveString);
		writer.close();
	}
}