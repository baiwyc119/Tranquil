#import <Foundation/Foundation.h>

#ifdef DEBUG
    #define TQLog(fmt, ...) NSLog(@"%s:%u (%s): " fmt "\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__)
    #define TQLog_min(fmt, ...)  NSLog(fmt "\n", ## __VA_ARGS__)


#define TQAssert(cond, fmt, ...) \
    do { \
        if(!(cond)) { \
            TQLog(@"Assertion failed: " fmt, ##__VA_ARGS__); \
            [NSException raise:@"TQAssertFailed" format:fmt, ##__VA_ARGS__]; \
        } \
    } while(0)

    #define TQAssertSoft(cond, errDomain, errCode, retVal, fmt, ...) \
    do { \
        if(!(cond)) { \
            if(aoErr) { \
                NSString *errorDesc = [NSString stringWithFormat:fmt, ##__VA_ARGS__]; \
                NSDictionary *userInfo = [NSDictionary dictionaryWithObject:errorDesc \
                                                                     forKey:NSLocalizedDescriptionKey]; \
                *aoErr = [NSError errorWithDomain:(errDomain) code:(errCode) userInfo:userInfo]; \
            } \
          /*  TQLog(fmt, ##__VA_ARGS__); */\
            return retVal; \
        } \
    } while(0)

#else
    #define TQLog(fmt, ...)
    #define TQAssert(cond, fmt, ...) cond
    #define TQAssertSoft(cond, errDomain, errCode, retVal, fmt, ...) cond
#endif

extern NSString * const kTQSyntaxErrorDomain;
extern NSString * const kTQGenericErrorDomain;
extern NSString * const kTQRuntimeErrorDomain;


typedef enum {
    kTQUnexpectedIdentifier = 1,
    kTQInvalidClassName,
    kTQInvalidAssignee,
    kTQUnexpectedStatement,
    kTQUnexpectedExpression,
    kTQUndefinedVariable,
    kTQObjCException,
    kTQGenericError
} TQSyntaxErrorCode;

