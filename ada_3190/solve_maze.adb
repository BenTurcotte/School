------------------------------------------
--       name:  Ben Turcotte            --
--         ID:  Bturcott                --
--          #:  0832217                 --
--      email:  bturcott@mail.guelph.ca --
-- assignment:  2                       --
--      class:  CIS*3190                --
------------------------------------------
with ada.text_io;              use ada.text_io;
with ada.integer_text_io;      use ada.integer_text_io;
with ada.text_io.unbounded_io; use ada.text_io.unbounded_io;
with ada.strings.unbounded;    use ada.strings.unbounded;
procedure solve_maze is
-- declarative section
  type Direction is (n, s, e, w);
  type Stack     is Array(positive range <>) of Direction;
  type Coord     is Array(1..2) of Integer;
  type Matrix_50 is Array(1..50, 1..50) of Character;

  file     : File_type;
  filename : Unbounded_string;
  line     : Unbounded_string;
  line_len : Integer;
  char     : Character;
  height   : Integer := 0;
  width    : Integer := 0;
  im_at    : Coord   := (0, 0);
  maze     : Matrix_50;

-- executable section
begin

  put("file name: ");
  get_line(filename);
  open(File => file,
       Mode => In_file,
       Name => filename);
  line = get_line(file);

  loop exit when End_of_file(file);
    char := get(file);
  end loop;
  close(file);
end solve_maze;