package com.boi.extensions;

import android.database.ContentObserver;
import android.os.Handler;

public class VolumeObserver extends ContentObserver {

	public VolumeObserver(Handler handler) {
		super(handler);
		// TODO Auto-generated constructor stub
	}
	@Override
	public boolean deliverSelfNotifications() {
		return super.deliverSelfNotifications();
	}
	@Override
	public void onChange(boolean selfChange) {
		super.onChange(selfChange);
	}
}
