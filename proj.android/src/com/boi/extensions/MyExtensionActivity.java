package com.boi.extensions;

import java.io.File;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxHelper;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.media.AudioManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.PowerManager;
import android.os.Vibrator;
import android.util.Log;
import android.widget.Toast;

public class MyExtensionActivity extends Cocos2dxActivity {

	public static MyExtensionActivity _activity;
	public static VolumeObserver mVolumeObserver;
	private static Vibrator sVibrateService = null;
	private static AudioManager mAudioManager = null;
	public static String[] allFilesName;
	public static List<File> list;
	public static PowerManager pm;
	public static PowerManager.WakeLock wl;
	public MyExtensionActivity() {
		// TODO Auto-generated constructor stub
	}
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		_activity = this;
		mVolumeObserver = new VolumeObserver(new Handler());
		this.getApplicationContext().getContentResolver().registerContentObserver(android.provider.Settings.System.CONTENT_URI, true, mVolumeObserver);
		Log.d("COCOS", "onCREATE");
		
	}
	@Override
	protected void onDestroy() {
		super.onDestroy();
		this.getApplicationContext().getContentResolver().unregisterContentObserver(mVolumeObserver);
	}
	public static List<File> getListFiles(File parentDir) {
	 	   ArrayList<File> inFiles = new ArrayList<File>();
	 	    File[] files = parentDir.listFiles();
	 	    if(files.length <=0) return inFiles;
	 	    for (File file : files) {
	 	        if (file.isDirectory()) {
	 	            inFiles.addAll(getListFiles(file));
	 	        } else {
	 	            if(file.getName().endsWith(".mp3")){
	 	                inFiles.add(file);
	 	            }
	 	        }
	 	    }
	 	    return inFiles;
	    }
	public static String getFileNameAtIndex(int index) {
 	   if(index >= 0 && index <= list.size()) {
 		   Log.d("GET FILE NAME",list.get(index-1).getName());
 		   return list.get(index-1).getName();
 	   }
 	   return "";
   	}
	public static int preLoad(String path) {
		Log.d("PATH from C", path);
		String s = Environment.getExternalStorageDirectory().getPath();
 		list = getListFiles(new File(s+path));
 		Log.d("SIZE", ""+list.size());
 		return list.size();
	}
	public static void logJNI() {
		String tag = "JNITest";
		String message = "Here is code in Android native";
		Log.d(tag, message);
		
	}
	public static String getPath() {
		String s = "";
		s = Environment.getExternalStorageDirectory().getPath();
		return s;
	}
	public static void testCocosHelper() {
	}
	public static void setScreenStayOn() {
		pm = (PowerManager) getContext().getSystemService(Context.POWER_SERVICE);
		wl = pm.newWakeLock(PowerManager.SCREEN_DIM_WAKE_LOCK | PowerManager.ON_AFTER_RELEASE, "Cocos");
		wl.acquire();
	}
	public static void unsetScreenStayOn() {
		wl.release();
	}
	public static void setVolume(int percent) {
		MyExtensionActivity.mAudioManager = (AudioManager)getContext().getSystemService(Context.AUDIO_SERVICE);
		int maxVolume = mAudioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
		double volume = maxVolume*percent/100;
		Log.d("VOLUME", "PERCENT: "+percent);
		try {
			int index = (int)volume;
			Log.d("VOLUME", "VALUE: "+index);
			mAudioManager.setStreamVolume(AudioManager.STREAM_MUSIC, index, 0);
		} catch (Exception e) {
			// TODO: handle exception
			Log.d("EXCEPTION", ""+e.toString());
		}
	}
	public static int getVolume() {
		int percent = 0;
		MyExtensionActivity.mAudioManager = (AudioManager)getContext().getSystemService(Context.AUDIO_SERVICE);
		try {
			float maxVolume = mAudioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
			float curentVolume = mAudioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
			percent =Math.round((curentVolume*100.0f)/maxVolume);
			Log.d("VOLUME", "percent = "+percent +"max: "+maxVolume + " current: "+curentVolume);
		} catch (Exception e) {
			Log.d("EXCEPTION getVolume", ""+e.toString());
		}
		return percent;
	}

	public static boolean isVibrateSupported() {
		boolean ret = true;
		MyExtensionActivity.sVibrateService = (Vibrator)getContext().getSystemService(Context.VIBRATOR_SERVICE);
		try {
			Method hasVibratorMethod = sVibrateService.getClass().getMethod("hasVibrator", (Class<?>[])null);
			Object result = hasVibratorMethod.invoke(sVibrateService);
			ret =(Boolean)result;
		} catch (Exception e) {
			// TODO: handle exception
			ret = false;
		}
		return ret;
	}
	public static void makeVibrate(int duration) {
		sVibrateService.vibrate(duration);
	}
	public static void stopVibrate() {
		sVibrateService.cancel();
	}
	public static void callPhone(String number) {
		Log.d("NUMBER",""+ Uri.parse(number));
		try {
			Intent callIntent = new Intent(Intent.ACTION_CALL);
			callIntent.setData(Uri.parse(number));
			//getContext().startActivity(callIntent);
			Cocos2dxHelper.getActivity().startActivity(callIntent);
		} catch (Exception e) {
			// TODO: handle exception
			Log.e("COCOS", "in make Call "+e.toString());
		}
		
	}
	
	public static void checkDevice() {
		try {
			if("google_sdk".equals(Build.PRODUCT) || Build.FINGERPRINT.startsWith("generic") || "sdk".equals(Build.PRODUCT)|| "sdk_x86".equals(Build.PRODUCT) ) {
				/*Toast.makeText(_activity, "REAL DEVICE. NAME: "+Build.DEVICE, 
						Toast.LENGTH_SHORT).show(); */
				Log.d("COCOS", "REAL DEVICE "+Build.DEVICE);
			}else {
				/*Toast.makeText(_activity, "EMULATOR. CREATOR: "+Build.MANUFACTURER, 
						Toast.LENGTH_SHORT).show();*/
				Log.d("COCOS", "SIMULATOR "+Build.DEVICE);
			}
			
			String mesage = "NAME: "+Build.DEVICE+"\nCREATOR: "+Build.MANUFACTURER+"\nVERSION: "+Build.VERSION.CODENAME+"\nID: "+Build.ID+"\nPRODUCT: "+Build.PRODUCT+"\nFINGERPRINT: "+Build.FINGERPRINT+"\nMODEL: "+Build.MODEL+"\nHOST: "+Build.HOST;
			Log.d("COCOS", mesage);
		}catch (Exception e) {
			/*Toast.makeText(_activity, "UNKNOW EXCEPTION", 
					Toast.LENGTH_SHORT).show();*/
			Log.d("COCOS", "in check device "+e.toString());
			return;
		}
		/*_activity.runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				String mesage = "NAME: "+Build.DEVICE+"\nCREATOR: "+Build.MANUFACTURER+"\nVERSION: "+Build.VERSION.CODENAME+"\nID: "+Build.ID+"\nPRODUCT: "+Build.PRODUCT+"\nFINGERPRINT: "+Build.FINGERPRINT+"\nMODEL: "+Build.MODEL+"\nHOST: "+Build.HOST;
				new AlertDialog.Builder(getContext()).setTitle("INFO").setMessage(mesage).setPositiveButton("YES", new DialogInterface.OnClickListener() {
					
					@Override
					public void onClick(DialogInterface dialog, int which) {
						// TODO Auto-generated method stub
						PackageManager pm = _activity.getPackageManager();
						try {
							pm.getPackageInfo("com.facebook.katana", PackageManager.GET_ACTIVITIES);
						}catch(PackageManager.NameNotFoundException e) {
							Toast.makeText(_activity, e.toString(), Toast.LENGTH_SHORT).show();
							return;
						}
						Toast.makeText(_activity, "FACE WAS INSTALLED", Toast.LENGTH_LONG).show();
					}
				}).show();
			}
		});*/
	}
}
