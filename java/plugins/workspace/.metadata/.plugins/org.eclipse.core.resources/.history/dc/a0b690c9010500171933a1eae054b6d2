package me.commandcraft.chestbank;

import java.io.IOException;

import org.bukkit.Bukkit;
import org.bukkit.event.Listener;
import org.bukkit.plugin.RegisteredServiceProvider;
import org.bukkit.plugin.java.JavaPlugin;

import me.commandcraft.chestbank.bank.BankManager;
import net.milkbowl.vault.permission.Permission;

public class ChestBank extends JavaPlugin {

	private static ChestBank instance;
	private static BankManager bankManager;
	private static Configuration configuration;
	private static Permission permission;
	
	public void onEnable() {
		instance = this;
		try {
			bankManager = new BankManager();
			Bukkit.getPluginManager().registerEvents(bankManager, this);
		} catch (IOException e) {
			e.printStackTrace();
		}
		configuration = new Configuration();
		if (!setupPermissions() || !permission.hasGroupSupport()) {
			Bukkit.getLogger().severe("[" + getDescription().getName() + "] Disabling because no permission was found");
			Bukkit.getPluginManager().disablePlugin(this);
			return;
		}
		this.getCommand("chestbank").setExecutor(new CommandExec());
	}
	
	public void onDisable() {
		try {
			bankManager.save();
			configuration.save();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void registerEvent(Listener event) {
		Bukkit.getPluginManager().registerEvents(event, this);
	}
	
	public boolean setupPermissions() {
	    RegisteredServiceProvider<Permission> permissionProvider = this.getServer().getServicesManager()
	            .getRegistration(net.milkbowl.vault.permission.Permission.class);
	    if (permissionProvider != null) {
	        permission = permissionProvider.getProvider();
	    }
	    return (permission != null);
	}
	
	public static ChestBank getInstance() {
		return instance;
	}
	
	public static BankManager getBankManager() {
		return bankManager;
	}
	
	public static Configuration getConfiguration() {
		return configuration;
	}
	
	public static Permission getPermission() {
		return permission;
	}
}
