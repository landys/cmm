Symble Table as Below:
  t IntT
  d IntT
  j IntT
  i IntT

Syntax Tree as Below:
  Output
    Const: 62
  Assign to: t
    Input
  Assign to: t
    Op: -
      Id: t
      Const: 48
  Assign to: i
    Op: -
      Op: +
        Id: t
        Const: 1
      Op: /
        Id: t
        Const: 2
  Assign to: j
    Op: -
      Op: +
        Const: 2
        Op: *
          Const: 3
          Const: 4
      Const: 6
  Assign to: d
    Op: +
      Op: +
        Op: +
          Assign to: i
            Op: *
              Const: 2
              Const: 2
          Op: /
            Op: *
              Id: j
              Const: 2
            Const: 4
        Id: t
      Const: 97
  Output
    Const: 10
  Output
    Const: 32
  Output
    Const: 100
  Output
    Const: 61
  Output
    Const: 39
  Output
    Id: d
  Output
    Const: 39
  Output
    Const: 32
  Output
    Const: 58
  Output
    Const: 41
  ReturnK
    Const: 0
