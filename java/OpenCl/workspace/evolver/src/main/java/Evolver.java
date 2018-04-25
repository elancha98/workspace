import java.io.File;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.security.InvalidParameterException;
import java.util.Arrays;

/**
 * Created by ernesto on 20/06/17.
 */
public class Evolver {

    private Organism[] generation;
    private RandomUtil random;
    private DBHandler dbHandler;

    private Method fitness;

    public Evolver(long seed, Method fitness, Organism[] generation, File db) {
        new Evolver(fitness, generation, db);
        this.random = new RandomUtil(seed);
    }

    public Evolver(long seed, Method fitness, Class<Organism> organism, int generationSize, File db) {
        new Evolver(fitness, organism, generationSize, db);
        this.random = new RandomUtil(seed);
    }

    public Evolver(Method fitness, Class<Organism> organism, int generationSize, File db) {
        random = new RandomUtil();
        this.fitness = fitness;
        generation = new Organism[generationSize];
        try {
            for (int i = 0; i < generationSize; i++) {
                generation[i] = organism.newInstance();
            }
        } catch (InstantiationException | IllegalAccessException e) {
            throw new IllegalArgumentException("Class \"organism\" provided is invalid. It must have a way to create" +
                    "a new Instance without any arguments");
        }
        dbHandler = new DBHandler(db);
    }

    public Evolver(Method fitness, Organism[] generation, File db) {
        random = new RandomUtil();
        this.fitness = fitness;
        this.generation = generation;
        dbHandler = new DBHandler(db);
    }

    public void nextGenerationKeep(int killed) {
        normalize();
        float min = generation[0].getFitness();
        float max = generation[generation.length - 1].getFitness();
        int saved = generation.length - killed;
        Organism[] next = new Organism[generation.length];
        Organism compare = new Organism();
        float min2 = max;
        float max2 = min;
        for (int i = 0; i < saved; i++) {
            float sel = random.random(min, max);
            compare.setFitness(sel);
            int org = Arrays.binarySearch(generation, compare);
            next[i] = generation[org];
            min2 = Math.min(min2, generation[org].getFitness());
            max2 = Math.max(max2, generation[org].getFitness());
        }
        Arrays.sort(next);
        for (int i = 0; i < killed; i++) {
            reproduce2(random, next, next, min2, max2, i+saved);
        }
        generation = next;
        System.gc();
    }

    public void nextGeneration() {
        normalize();
        float min = generation[0].getFitness();
        float max = generation[generation.length - 1].getFitness();
        Organism[] next = new Organism[generation.length];
        for (int i = 0; i < generation.length; i++) {
            reproduce2(random, generation, next, min, max, i);
        }
        generation = next;
        System.gc();
    }

    public void quickGeneration() {
        try {
            fitness.invoke(null, generation);
        } catch (IllegalAccessException | InvocationTargetException e) {
            throw new InvalidParameterException("given function \"fitness\" error, it must be static and get" +
                    "an Organism[] as arguments");
        }
        sort();
        saveGeneration();
        nextGeneration();
    }

    public void quickGenerationShort(int killed) {
        try {
            fitness.invoke(null, generation);
        } catch (IllegalAccessException | InvocationTargetException e) {
            throw new InvalidParameterException("given function \"fitness\" error, it must be static and get" +
                    "an Organism[] as arguments");
        }
        sort();
        saveGeneration();
        nextGenerationKeep(killed);
    }

    public void sort() {
        Arrays.sort(generation);
    }

    public void normalize() {
        float s = 0;
        for (int i = 0; i < generation.length; i++) {
            s += generation[i].getFitness();
            generation[i].setFitness(s);
        }
    }

    public void saveGeneration() {
        dbHandler.writeGeneration(generation);
    }

    public Organism[] getGeneration(int number) {
        return dbHandler.readGeneration(number);
    }

    public Organism getBest(int generation) {
        return dbHandler.readOrganism(generation, this.generation.length - 1);
    }

    public Organism getWorst(int generation) {
        return dbHandler.readOrganism(generation, 0);
    }

    public Organism getMedium(int generation) {
        return dbHandler.readOrganism(generation, this.generation.length / 2);
    }

    private static void reproduce2(RandomUtil random, Organism[] generation, Organism[] next,
                                   float min, float max, int i) {
        Organism compare = new Organism();
        float sel1 = random.random(min, max);
        compare.setFitness(sel1);
        int o1 = Arrays.binarySearch(generation, compare);
        float sel2 = random.random(min, max);
        compare.setFitness(sel2);
        int o2 = Arrays.binarySearch(generation, compare);
        next[i] = generation[o1].reproduce(generation[o2]);
    }
}
