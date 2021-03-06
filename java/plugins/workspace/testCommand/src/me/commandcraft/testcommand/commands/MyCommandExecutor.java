package me.commandcraft.testcommand.commands;

import java.util.Arrays;
import java.util.List;

import org.bukkit.Bukkit;
import org.bukkit.command.Command;
import org.bukkit.command.CommandSender;
import org.bukkit.command.TabExecutor;

import me.commandcraft.testcommand.CommandExec;

public class MyCommandExecutor implements TabExecutor {

	static final String[] COMMANDS = {"test"};

	@Override
	public List<String> onTabComplete(CommandSender arg0, Command arg1,
			String arg2, String[] arg3) {
		return Arrays.asList(new String[] {"1 ejemplo", "2 ejemplo"});
	}

	@Override
	public boolean onCommand(CommandSender sender, Command arg1, String arg2,
			String[] arg3) {
		@SuppressWarnings("rawtypes")
		List ent = CommandExec.getEntities(sender, arg3[0]);
		Bukkit.getLogger().info("Length: " + ent.size());
		return false;
	}

}
