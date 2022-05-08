public class Test {

	public static void main(String[] args) {
		Buffer buffer = new Buffer(5);
		
		new Thread(new Runnable() {
			
			@Override
			public void run() {
				while(true) {
					try {
						Thread.sleep(1_500);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					
					try {
						buffer.insert("A");
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		}).start();
		
		new Thread(new Runnable() {
					
			@Override
			public void run() {
				while(true) {
					try {
						Thread.sleep(1_500);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					
					try {
						buffer.insert("B");
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		}).start();
		
		new Thread(new Runnable() {
					
			@Override
			public void run() {
				while(true) {
					try {
						buffer.fetch();
						//System.out.println(buffer.fetch());
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		}).start();
	}

}
