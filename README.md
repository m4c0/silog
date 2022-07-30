# silog

Simple multi-platform logging for C++

This library exports one function. Call it to generate a simple log that
"matches" what's expected in each platform:

```
silog::log(silog::error, "ok");
```

On Windows, it adds a line into a log file named after the running executable.

On MacOSX/iOS, it calls `NSLog`. It becomes visible on console and available via Apple's log infrastructure.

On Android, it calls `android_log`. It can be consumed via `adb`.
