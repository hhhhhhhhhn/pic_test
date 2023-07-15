#![no_std]
#![no_main]

const STR: &str = "Data\0";
const MAGIC: [i32; 5] = [0, 1, 2, 3, 4];

#[no_mangle]
pub extern "C" fn _start() -> *const u8 {
    return STR.as_ptr();
}

fn add(a: i32, b: i32) -> i32 {
    return a + b
}

fn fib(n: i32) -> i32 {
    if n <= 1 {
        return 1
    }
    return fib(n - 1) + fib(n - 2)
}

#[panic_handler]
extern "C" fn panic(_info: &core::panic::PanicInfo) -> ! {
    loop {}
}
