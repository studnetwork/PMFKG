
KeyboardFocusManager manager = KeyboardFocusManager.getCurrentKeyboardFocusManager();
manager.addKeyEventDispatcher("pokazivac na instancu KeyEventDispatcher");

public boolean dispatchKeyEvent(KeyEvent e) {
		
		if(e.getID() == KeyEvent.KEY_PRESSED)
		{
			switch(e.getKeyCode())
			{
			case KeyEvent.VK_UP:
				break;
			case KeyEvent.VK_DOWN:
				break;
			case KeyEvent.VK_LEFT:
				break;
			case KeyEvent.VK_RIGHT:
				break;
			}
		}
		
		return false;
	}
