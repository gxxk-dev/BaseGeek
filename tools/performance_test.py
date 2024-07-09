import gc,utime
def Test(TestFunc):
    ram1=gc.mem_free()
    time1=utime.ticks_us()
    TestFunc()
    return [utime.ticks_us()-time1,gc.mem_free()-ram1]
def MultiTest(data):
    for name,func in enumerate(data):
        time_,ram_=Test(func)
        print("{}  Time{}us ram{}bytes".format(name,time_,ram_))
        