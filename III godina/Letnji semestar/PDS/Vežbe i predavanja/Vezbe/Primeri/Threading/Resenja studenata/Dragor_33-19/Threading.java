import java.util.ArrayList;
import java.util.concurrent.locks.ReentrantLock;

/* Legenda

[X] -oznacava zakljucavanje
[ ] -oznacava otkljucavanje

*/

/* Opis koda

Kod simulira komunikaciju izmedju dve niti, jedna upisuje poruke u bafer (lista stringova), a druga uzima i ispisuje poruke iz tog bafera.
Bafer se prvo puni do odredjenog broja poruka, nakon cega se prazni sve dok vise nema poruka u njemu.

Konkurentni pristup objektima je regulisan pomocu ReentrantLock klase.
Instanca te klase predstavlja katanac (lock) koga zakljcava nit koja prva izvrsi lock() metodu instance, a ostale niti kada izvrse istu metodu iste instance blokiraju se i cekaju dok prva nit ne otkljuca lock.

*/

public class Threading {

    public static void main(String[] args) 
    {
        // Bafer za smestanje poruka
        ArrayList<String> buff = new ArrayList<String>();

        // Test 1 - Kreiraju se i pokrecu 2, jedna salje a jedna prima poruke
        // new Sender(buff, "S").start();
        // new Receiver(buff, "R").start();

        // Test 2 - Kreiraju se i pokrecu 2 niti koje salju i 2 koje primaju poruke
        new Sender(buff, "S1").start();
        new Sender(buff, "S2").start();
        new Receiver(buff, "R1").start();
        new Receiver(buff, "R2").start();

    }
}

class Nit extends Thread 
{
    public static final int MAX_BUFF_SIZE = 3;                           // Maksimalan broj poruka u baferu (nakon cega pocinje da se prazni)
    public static final ReentrantLock lockBuff = new ReentrantLock();    // Lock koji obezbedjuje da samo jedna nit pristupa (cita ili pise) baferu
    public static final ReentrantLock lockFlag = new ReentrantLock();    // Lock koji obezbedjuje da samo jedna nit pristupa (cita ili pise) indikatoru za praznjenje bafera (boolean flagFlush)
    public static boolean flagFlush;                                     // Indikator za praznjenje bafera (ako je true znaci da bafer treba da se isprazni)

    public ArrayList<String> buff;                                       // Bafer za upisivanje i uzimanje poruka
    public String threadName;                                            // Sluzi samo za ispisivanje u konzoli, da bi se znalo koja je nit sta ispisala
    
    public Nit(ArrayList<String> buff, String threadName)
    {
        this.buff = buff;
        flagFlush = false; // na pocetku je bafer prazan, pa ne treba/moze da se prazni
        
        this.threadName = threadName;
    }
}

class Sender extends Nit 
{
    public Sender(ArrayList<String> buff, String threadName) {
        super(buff, threadName);
    }
    
    @Override
    public void run()
    {
        // Beskonacno puta se poziva send()
        while (true) {
            try { send(); } 
            catch (Exception e) { e.printStackTrace(); }
        }
    }
    
    // Jedno izvrsavanje metode moze upisati jednu poruku u bafer, ili preskociti upisivanje ukoliko je dovoljno pun
    public void send() throws Exception
    {    
        System.out.println(threadName + " | BEGIN");
        
        System.out.println(threadName + " | Lock Flag");
        lockFlag.lock(); // flag [X]
        
        if (flagFlush == false) 
        {    
            lockBuff.lock(); // buff [X]

            // Dodavanje jedne poruke
            if (buff.size() < MAX_BUFF_SIZE) {
                buff.add("\"Poruka iz niti " + threadName + "\"");
                System.out.println(threadName + " | Add to Buffer, new size: " + buff.size());
            }
            // Dodavanje se preskace
            else {                                
                flagFlush = true;
            }
            
            System.out.println(threadName + " | Unlock Flag (if)");
            lockFlag.unlock(); // flag [ ]

            System.out.println(threadName + " | Unlock Buff");
            lockBuff.unlock(); // buff [ ]
        }
        else {
            System.out.println(threadName + " | Unlock Flag (else)");
            lockFlag.unlock(); // flag [ ]
        }
        
        
        System.out.println(threadName + " | Sleep...");
        sleep(2000);
        System.out.println(threadName + " | END");
    }
}

class Receiver extends Nit
{
    public Receiver(ArrayList<String> buff, String threadName) {
        super(buff, threadName);
    }
    
    @Override
    public void run()
    {
        // Beskonacno puta se poziva receive()
        while (true) {
            try { receive(); } 
            catch (Exception e) { e.printStackTrace(); }
        }
    }
    
    // Jedno izvrsavanje metode moze uzeti jednu poruku iz bafera, ili preskociti uzimanje ukoliko je bafer prazan
    public void receive() throws Exception
    {    
        System.out.println(threadName + " | BEGIN");

        System.out.println(threadName + " | Lock Flag");
        lockFlag.lock(); // flag [X]
        
        if (flagFlush == true)
        {    
            lockBuff.lock(); // buff [X]

            // Citanje jedne poruke
            if (buff.size() > 0) {
                String msg = buff.remove(0);
                System.out.println(threadName + " | Remove from Buffer, new size: " + buff.size() + ", received message: " + msg);
            }
            // Citanja se preskace
            else {
                flagFlush = false;
            }
            
            System.out.println(threadName + " | Unlock Flag (if)");
            lockFlag.unlock(); // flag [ ]

            System.out.println(threadName + " | Unlock Buff");
            lockBuff.unlock(); // buff [ ]
        }
        else {
            System.out.println(threadName + " | Unlock Flag (else)");
            lockFlag.unlock(); // flag [ ]
        }

        System.out.println(threadName + " | Sleep...");
        sleep(2000);
        System.out.println(threadName + " | END");
    }
}
