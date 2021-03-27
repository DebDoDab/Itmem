class System {
    companion object {
        var day: Int = 0
            set(value) {
                if (value > field) {
                    field = value
                }
            }
    }
}