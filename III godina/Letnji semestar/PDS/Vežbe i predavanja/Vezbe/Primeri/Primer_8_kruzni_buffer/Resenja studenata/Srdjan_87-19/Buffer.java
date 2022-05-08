// Resenje sa kruznim buffer-om bez promenljive count

/*
 * Koriscenje brakepoint-a (debugging mode-a) moze omoguciti brzi dolazak do
 * nesekvencijalnih izvrsavanja, pa je pogodno za koriscenje kada je potrebno
 * uociti ponasanje u razlicitim slucajevima ili ponasanje samog kruznog buffer-a
 * 
 * Predlog: breakpoint-e postavljati unutar metoda 'insert' i 'fetch'
 * */

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Buffer {
	private int fetchPointer = 0;
	private int insertPointer = 0;
	private String character;
	private final int capacity;
	private final String[] buffer;
	private final Lock lock = new ReentrantLock(true);
	private final Condition notFull = lock.newCondition();
	private final Condition notEmpty = lock.newCondition();
	
	public Buffer(int capacity) {
		this.capacity = capacity;
		buffer = new String[capacity];
	}

	public void insert(String s) throws InterruptedException {
		lock.lock();
		
		// ako je sledeca pozicija za dodavanje pozicija sa koje ce da se skine
		// element onda je bafer pun
		while((insertPointer+1) % capacity == fetchPointer) 
			 notFull.await();

		try {
			buffer[insertPointer] = character = s;
			insertPointer = (insertPointer+1) % capacity;
			notEmpty.signal();
		} finally {
			System.out.println("insert " + character +": " + toString());
			lock.unlock();
		}
		
	}
	
	public String fetch() throws InterruptedException {
		lock.lock();
		
		// ako je pozicija sa koje se skida element ista pozicija na koju treba
		// dodati element onda je bager prazan
		while(fetchPointer == insertPointer) 
			notEmpty.await();

		try {
			String s = character = buffer[fetchPointer];
			fetchPointer = (fetchPointer+1) % capacity;
			notFull.signal();
			return s;
		} finally {
			System.out.println("fetch  " + character + ": " + toString());
			lock.unlock();
		}
		
	}
	
	public String toString() {
		String representation = "[";
		lock.lock();
		
		try {
			if( (fetchPointer < insertPointer && fetchPointer <= 0 && 0 < insertPointer) 
					|| (fetchPointer > insertPointer 
							&& ( 0 >= fetchPointer || 0 < insertPointer))) {
				representation += buffer[0];
			}
			else
				representation += "?";
			
			for (int i = 1; i < capacity; i++) {
				if( (fetchPointer < insertPointer && fetchPointer <= i && i < insertPointer) 
						|| (fetchPointer > insertPointer 
							&& ( i >= fetchPointer || i < insertPointer))) {
					representation += ", " + buffer[i];
				}
				else
					representation += ", ?";
			}
		} finally {
			lock.unlock();
		}
		
		return representation + "]";
	}
}


// resenje sa bufferom koji nije kruzni

//import java.util.ArrayList;
//import java.util.List;
//import java.util.concurrent.locks.Condition;
//import java.util.concurrent.locks.Lock;
//import java.util.concurrent.locks.ReentrantLock;
//
//public class Buffer {
//	private int count = 0;
//	private final int capacity;
//	private final List<String> buffer;
//	private final Lock lock = new ReentrantLock(true);
//	private final Condition notFull = lock.newCondition();
//	private final Condition notEmpty = lock.newCondition();
//	
//	public Buffer(int capacity) {
//		this.capacity = capacity;
//		buffer = new ArrayList<String>(capacity);
//	}
//
//	public void insert(String s) throws InterruptedException {
//		lock.lock();
//		
//		while(count == capacity) 
//			 notFull.await();
//		
//		try {
//			buffer.add(s);
//			count++;
//			notEmpty.signal();
//		} finally {
//			lock.unlock();
//		}
//		
//	}
//	
//	public String fetch() throws InterruptedException {
//		lock.lock();
//		
//		while(count == 0) 
//			notEmpty.await();
//			
//		try {
//			String s = buffer.remove(buffer.size()-1);
//			count--;
//			notFull.signal();
//			return s;
//		} finally {
//			lock.unlock();
//		}
//		
//	}
//}
