extern crate scanner;

#[derive(Debug, Clone, Copy)]
struct Tetra {
    north: i32,
    east: i32,
    south: i32,
    west: i32,
}

impl Tetra {
    fn new(n: i32, e: i32, s: i32, w: i32) -> Tetra {
        Tetra {
            north: n,
            east: e,
            south: s,
            west: w,
        }
    }

    fn to_string(&self) -> String {
        format!("({}, {}, {}, {})", self.north, self.east, self.south, self.west)
    }
}

fn iter(tetras: &Vec<Tetra>, size: usize, pos: usize, field: &mut Vec<Vec<Tetra>>, used: &mut Vec<bool>) -> bool {
    if pos == size * size {
        return true;
    }

    let y = pos / size;
    let x = pos % size;

    for i in 0..(size * size) {
        if used[i] {
            continue;
        }
        if x != 0 && tetras[i].west != field[y][x - 1].east {
            continue;
        }
        if y != 0 && tetras[i].north != field[y - 1][x].south {
            continue;
        }

        used[i] = true;
        field[y][x] = tetras[i];
        if iter(tetras, size, pos + 1, field, used) {
            return true;
        }
        used[i] = false;
    }

    return false;
}

fn make_vec<T: Copy>(len: usize, v: T) -> Vec<T> {
    let mut vs = Vec::new();
    vs.resize(len, v);

    vs
}

fn make_matrix<T: Copy>(height: usize, width: usize, v: T) -> Vec<Vec<T>> {
    let mut row = Vec::new();
    row.resize(width, v);

    let mut col = Vec::new();
    col.resize(height, row);

    col
}

fn solve(tetras: Vec<Tetra>, size: usize) {
    let mut field = make_matrix(size, size, Tetra::new(0, 0, 0, 0));
    let mut used = make_vec(size * size, false);

    if !iter(&tetras, size, 0, &mut field, &mut used) {
        println!("Impossible");
        return;
    }

    for i in 0..size {
        for j in 0..size {
            println!("{}", field[i][j].to_string());
        }
        println!("");
    }
}

fn main() {
    let mut sc = scanner::from_stdin();

    loop {
        let size = sc.next::<usize>().unwrap();
        if size == 0 {
            break;
        }
        // println!("size = {}", size);

        let mut tetras = Vec::<Tetra>::new();
        for _ in 0 .. (size * size) {
            let n = sc.next::<i32>().unwrap();
            let w = sc.next::<i32>().unwrap();
            let e = sc.next::<i32>().unwrap();
            let s = sc.next::<i32>().unwrap();

            // println!("(n, w, e, s) = ({}, {}, {}, {})", n, w, e, s);
            tetras.push(Tetra::new(n, e, s, w));
        }

        solve(tetras, size);
    }
}
