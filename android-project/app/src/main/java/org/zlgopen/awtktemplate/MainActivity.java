package org.zlgopen.awtktemplate;

import android.os.Bundle;
import android.content.Intent;
import org.libsdl.app.SDLActivity;
import org.zlgopen.plugins.PluginManager;

public class MainActivity extends SDLActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        PluginManager.start(this);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        PluginManager.stop();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        PluginManager.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode,
          String[] permissions, int[] grantResults) {
        PluginManager.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }

    @Override
    protected String getMainFunction() {
        return "SDL_main";
    }

    @Override
    public void onSystemUiVisibilityChange(int visibility) {
    }

    @Override
    protected String[] getLibraries() {
        return new String[] {
                "awtk",
                "app"
        };
    }

}
