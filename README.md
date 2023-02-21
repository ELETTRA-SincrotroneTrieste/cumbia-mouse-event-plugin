### Cumbia mouse events plugin

cumbia-qtcontrols widgets that use CuMouseEvHandler to intercept mouse events can load this plugin
that offers additional functionalities.

To install the plugin, execute

- qmake
- make
- make install

after checking that the line

```
include(/usr/local/cumbia-libs/include/cumbia-qtcontrols/cumbia-qtcontrols.pri)
```

in the file cumbia-mouse-event-plugin.pro is correct (in the default case,
cumbia-qtcontrols is installed under /usr/local/cumbia-libs)

#### Drag events

The plugin offers a drag event containing either the *source* or *target* of readers
(writers) as source, in plain text

Have fun.


