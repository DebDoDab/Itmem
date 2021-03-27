package system

class System {
    companion object {
        var currentTime: Int = 0
            set(value: Int) {
                if (value > currentTime) field = value
            }
    }
}