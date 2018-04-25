import java.util.Random;

/**
 * Created by ernesto on 22/06/17.
 */
public class RandomUtil {

    private Random random;

    public RandomUtil() {
        random = new Random();
    }

    public RandomUtil(long seed) {
        random = new Random(seed);
    }

    public float random(float min, float max) {
        return random.nextFloat() * (min - max) + min;
    }
}
