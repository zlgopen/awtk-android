package org.zlgopen.awtktemplate;

import android.os.Bundle;
import org.libsdl.app.SDLActivity;

public class MainActivity extends SDLActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
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
