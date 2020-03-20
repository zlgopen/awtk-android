package org.zlgopen.plugins;

import java.util.Set;
import java.util.Map;
import android.util.Log;
import java.util.HashMap;
import java.util.Iterator;
import android.app.Activity;

public class PluginManager {
  public static void start(Activity activity) {
    Log.v("AWTK", "PluginManager(dummy) start");
  }
  
  public static void stop() {
    Log.v("AWTK", "PluginManager(dummy) stop");
  }

  public static void onActivityResult(int requestCode, int resultCode, Intent data) {
    Log.v("AWTK", "PluginManager(dummy) onActivityResult");
  }
}
