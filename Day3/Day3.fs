module Program

// Convert a character to it's numerical equivalent
let charToInt c = int c - int '0'


[<EntryPoint>]
let main argv = 
//     let inputString = "5\t9\t2\t8
// 9\t4\t7\t3
// 3\t8\t6\t5"
    let walker =
        let x = ref 0
        let y = ref 0
        fun step ->
            x := (x) + 1
            y := (y) - 1

    walker.step()
    walker.step()

    // printfn "Part1: %A" part1
    // printfn "Part2: %A" part2seq

    0 // return an integer exit code
