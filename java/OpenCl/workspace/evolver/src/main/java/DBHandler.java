import org.mapdb.DB;
import org.mapdb.DBMaker;

import java.io.File;
import java.util.Iterator;
import java.util.Set;

/**
 * Created by ernesto on 20/06/17.
 */


public class DBHandler {

    private DB db;
    private Set<Organism[]> set;

    public DBHandler(File file) {
        db = DBMaker.fileDB(file).closeOnJvmShutdown().make();
        set = db.treeSet("generations").serializer(Organism.serializer).createOrOpen();
    }

    public void writeGeneration(Organism[] organisms) {
        set.add(organisms);
        db.commit();
    }

    public Organism[] readGeneration(int number) {
        Iterator<Organism[]> iterator = set.iterator();
        for (int i = 0; i < number; i++) {
            iterator.next();
        }
        return iterator.next();
    }

    public Organism readOrganism(int generation, int number) {
        return readGeneration(generation)[number];
    }
}