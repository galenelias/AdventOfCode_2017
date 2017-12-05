module Program


// Super work in progress, not even close to working

// Convert a character to it's numerical equivalent
let charToInt c = int c - int '0'


[<EntryPoint>]
let main argv = 
    let walker =
        let x = ref 0
        let y = ref 0
        fun step ->
            x := (x) + 1
            y := (y) - 1

    walker.step()
    walker.step()


    0 // return an integer exit code
