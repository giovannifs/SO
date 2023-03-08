package prod_cons;

public class Producer implements Runnable {
    private SharedBoundedStack buffer;
    private int serviceTime;

    Producer(SharedBoundedStack b, int serviceTime)
    {
        this.buffer = b;
        this.serviceTime = serviceTime;
        new Thread((Runnable) this, "Producer").start();
    }

    public void run()
    {
        int i = 1;
        while (true) {
            // producer producing an item; the sleep just simulates the time to produce
            try {
                Thread.sleep(this.serviceTime);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            // producer put items
            System.out.println(String.format("Producer has produced %d", i));
            this.buffer.put(i++);
        }
    }
}
