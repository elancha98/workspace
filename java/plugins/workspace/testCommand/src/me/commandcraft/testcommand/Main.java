package me.commandcraft.testcommand;

import org.bukkit.plugin.java.JavaPlugin;

public class Main extends JavaPlugin {

	public void onEnable() {
		try {
			CommandExec.setCommands(this);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void onDisable() {

	}
}
