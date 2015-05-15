package com.boi.extensions;

import java.util.concurrent.Callable;
import java.util.concurrent.FutureTask;

import org.cocos2dx.lib.Cocos2dxHelper;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.util.Log;

public class AndroidNativeAlert {

	private static native void alertDidDismiss(String alertId, int index);
	
	public static void _alertDisDismiss(String alertId, int index) {
		alertDidDismiss(alertId, index);
	}

	public static String showNativeAlert(final String aTitle, final String aMsg, final String aCancelBtn, final String aReturnBtn, final String aOtherBtn) {
		
		FutureTask<String> task = new FutureTask<String>(new Callable<String>() {
			@Override
			public String call() throws Exception {
				AlertDialog.Builder builder = new AlertDialog.Builder(Cocos2dxHelper.getActivity());
				if(aTitle.length() > 0) builder.setTitle(aTitle);
				if(aMsg.length() >0 ) builder.setMessage(aMsg);
				
				DialogInterface.OnClickListener diaInterFace = new DialogInterface.OnClickListener() {
					
					@Override
					public void onClick(DialogInterface dialog, int id) {
						// TODO Auto-generated method stub
						dialog.cancel();
						
						AndroidNativeAlert._alertDisDismiss(""+dialog, id);
						
					}
				};
				if(aCancelBtn.length() > 0) {
					builder.setNegativeButton(aCancelBtn, diaInterFace);
					builder.setCancelable(true);
				}
				
				if(aReturnBtn.length() > 0) {
					builder.setPositiveButton(aReturnBtn, diaInterFace);
				}
				
				if(aOtherBtn.length() > 0) {
					builder.setNeutralButton(aOtherBtn, diaInterFace);
				}
				
				AlertDialog alert1 = builder.create();
				alert1.show();
				return ""+alert1;
			}
			
		});
		
		try {
			Cocos2dxHelper.getActivity().runOnUiThread(task);
			String alertId = task.get();
			return alertId;
		} catch (Exception e) {
			// TODO: handle exception
			Log.d("Android Native Alert", "show native exception = "+e.toString());
			return "";
		}
	}
}

