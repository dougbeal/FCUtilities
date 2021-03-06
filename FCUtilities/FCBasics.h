//
//  FCBasics.h
//  Part of FCUtilities by Marco Arment. See included LICENSE file for BSD license.
//

#import <Foundation/Foundation.h>

#define user_defaults_get_bool(key)   [[NSUserDefaults standardUserDefaults] boolForKey:key]
#define user_defaults_get_int(key)    ((int) [[NSUserDefaults standardUserDefaults] integerForKey:key])
#define user_defaults_get_double(key) [[NSUserDefaults standardUserDefaults] doubleForKey:key]
#define user_defaults_get_string(key) fc_safeString([[NSUserDefaults standardUserDefaults] stringForKey:key])
#define user_defaults_get_array(key)  [[NSUserDefaults standardUserDefaults] arrayForKey:key]
#define user_defaults_get_object(key) [[NSUserDefaults standardUserDefaults] objectForKey:key]

#define user_defaults_set_bool(key, b)   { [[NSUserDefaults standardUserDefaults] setBool:b    forKey:key]; [[NSUserDefaults standardUserDefaults] synchronize]; }
#define user_defaults_set_int(key, i)    { [[NSUserDefaults standardUserDefaults] setInteger:i forKey:key]; [[NSUserDefaults standardUserDefaults] synchronize]; }
#define user_defaults_set_double(key, d) { [[NSUserDefaults standardUserDefaults] setDouble:d  forKey:key]; [[NSUserDefaults standardUserDefaults] synchronize]; }
#define user_defaults_set_string(key, s) { [[NSUserDefaults standardUserDefaults] setObject:s  forKey:key]; [[NSUserDefaults standardUserDefaults] synchronize]; }
#define user_defaults_set_array(key, a)  { [[NSUserDefaults standardUserDefaults] setObject:a  forKey:key]; [[NSUserDefaults standardUserDefaults] synchronize]; }
#define user_defaults_set_object(key, o) { [[NSUserDefaults standardUserDefaults] setObject:o  forKey:key]; [[NSUserDefaults standardUserDefaults] synchronize]; }

#define APP_DISPLAY_NAME    [NSBundle.mainBundle objectForInfoDictionaryKey:@"CFBundleDisplayName"]
#define APP_VERSION     	[NSBundle.mainBundle objectForInfoDictionaryKey:@"CFBundleShortVersionString"]
#define APP_BUILD_NUMBER    [NSBundle.mainBundle objectForInfoDictionaryKey:@"CFBundleVersion"]

inline __attribute__((always_inline)) NSString *fc_safeString(NSString *str) { return str ? str : @""; }

inline __attribute__((always_inline)) NSString *fc_dictionaryValueToString(NSObject *cfObj)
{
    if ([cfObj isKindOfClass:[NSString class]]) return (NSString *)cfObj;
    else return [(NSNumber *)cfObj stringValue];
}

// If we're currently on the main thread, run block() sync, otherwise dispatch block() sync to main thread.
inline __attribute__((always_inline)) void fc_executeOnMainThread(void (^block)())
{
    if (block) {
        if ([NSThread isMainThread]) block(); else dispatch_sync(dispatch_get_main_queue(), block);
    }
}

// If we're currently on the main thread, run block() **sync**, otherwise dispatch block() **ASYNC** to main thread.
inline __attribute__((always_inline)) void fc_executeOnMainThreadAsync(void (^block)())
{
    if (block) {
        if ([NSThread isMainThread]) block(); else dispatch_async(dispatch_get_main_queue(), block);
    }
}


inline __attribute((always_inline)) uint64_t fc_random_int64()
{
    uint64_t urandom;
    if (0 != SecRandomCopyBytes(kSecRandomDefault, sizeof(uint64_t), (uint8_t *) (&urandom))) {
        arc4random_stir();
        urandom = ( ((uint64_t) arc4random()) << 32) | (uint64_t) arc4random();
    }
    return urandom;
}

