import org.jetbrains.annotations.NotNull;
import org.mapdb.DataInput2;
import org.mapdb.DataOutput2;
import org.mapdb.Serializer;
import org.mapdb.serializer.SerializerArray;

import java.io.*;


/**
 * Created by ernesto on 20/06/17.
 */
public class Organism implements Serializable, Comparable<Organism> {

    public static SerializerArray<Organism> serializer =
            new SerializerArray<>(new OrganismSerializer(), Organism.class);

    private float fitness; //Must be positive

    public Organism() {};

    public Organism reproduce(Organism other) {
        return new Organism();
    }

    @Override
    public int compareTo(Organism other) {
        return ((Float) this.fitness).compareTo(other.fitness);
    }

    public void setFitness(float fitness) {
        this.fitness = fitness;
    }

    public float getFitness() {
        return fitness;
    }


    private static final class OrganismSerializer implements Serializer<Organism> {
        @Override
        public void serialize(@NotNull DataOutput2 dataOutput, @NotNull Organism organism) throws IOException {
            ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
            ObjectOutputStream objectOutputStream = new ObjectOutputStream(outputStream);
            objectOutputStream.writeObject(organism);
            objectOutputStream.flush();
            dataOutput.write(outputStream.toByteArray());
        }

        @Override
        public Organism deserialize(@NotNull DataInput2 dataInput, int i) throws IOException {
            byte[] input = new byte[i];
            dataInput.readFully(input);
            ByteArrayInputStream inputStream = new ByteArrayInputStream(input);
            ObjectInputStream objectInputStream = new ObjectInputStream(inputStream);
            Organism o = null;
            try {
                o = (Organism) objectInputStream.readObject();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
            return o;
        }

        @Override
        public int compare(Organism o1, Organism o2) {
            return 0;
        }
    }
}