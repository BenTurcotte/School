------------------------------------------
--       name:  Ben Turcotte            --
--         ID:  Bturcott                --
--          #:  0832217                 --
--      email:  bturcott@mail.guelph.ca --
-- assignment:  2                       --
--      class:  CIS*3190                --
------------------------------------------

with ada.text_io, ada.integer_text_io, ada.text_io.unbounded_io, ada.strings.unbounded;
use  ada.text_io, ada.integer_text_io, ada.text_io.unbounded_io, ada.strings.unbounded;
with stack; use  stack; -- hey, this is the one I made! cool!

procedure a2 is

-- USER DEFINED TYPES
  type Cell is record
      piece   : Character;
      visited : Boolean;
    end record;
  type Can_go_next    is Array(1..4)    of Coordinate; -- 1, 2, 3, 4 correspond to north, south, east, west
  type Cell_matrix_50 is Array(1..50, 1..50) of Cell;


-- FUNCTIONS & PROCEDURES
  function has_neighbours(im_at : in Coordinate; maze : in Cell_matrix_50; width : in Integer; height : in Integer) return Boolean is
  begin
    if im_at.x > 0 and im_at.y > 0 and im_at.x < width and im_at.y < height then
      return true;
    end if;
    return false;
  end has_neighbours;


  procedure where_can_i_go(im_at : in Coordinate; maze : in Cell_matrix_50; width : in Integer; height : in Integer; can_go : out Can_go_next) is
  begin
    can_go := ((-1,-1), (-1,-1), (-1,-1), (-1,-1));
    if im_at.y > 0 and not maze(im_at.x, im_at.y -1).visited then -- can go north
      can_go(1).x := im_at.x;
      can_go(1).y := im_at.y -1;
    end if;
    if im_at.y < height and not maze(im_at.x, im_at.y +1).visited then -- can go south
      can_go(2).x := im_at.x;
      can_go(2).y := im_at.y +1;
    end if;
    if im_at.x < width and not maze(im_at.x +1, im_at.y).visited then -- can go east
      can_go(3).x := im_at.x +1;
      can_go(3).y := im_at.y;
    end if;
    if im_at.x > 0 and not maze(im_at.x -1, im_at.y).visited then -- can go west
      can_go(4).x := im_at.x -1;
      can_go(4).y := im_at.y;
    end if;
  end where_can_i_go;


  function is_dead_end(can_go : in Can_go_next) return Boolean is
  begin
    if can_go = ((-1,-1), (-1,-1), (-1,-1), (-1,-1)) then
      return true;
    end if;
    return false;
  end is_dead_end;


  -- interates through the Stack_of_coordinates & prints the direction of
  --   one element in relation to the previous element
  procedure print_solution(soln : in Stack_of_coordinates) is
  begin
    put("Solution: ");
    if soln(2) = (-1, -1) then
      put("no solution is possible."); new_line;
    else
      print_moves: for index in reverse 2..size(soln) loop
        if index < size(soln) then
          put(", ");
        end if;
        if    soln(index -1).y < soln(index).y then put("N");
        elsif soln(index -1).y > soln(index).y then put("S");
        elsif soln(index -1).x < soln(index).x then put("E");
        elsif soln(index -1).x > soln(index).x then put("W");
        end if;
      end loop print_moves;
    end if;
  end print_solution;


-- VAR DECLARATIONS
  filename : String(1..32);
  str_len  : Integer;
  file     : File_type;
  BUFFER   : Unbounded_string;
  char     : Character;
  height   : Integer := 0;
  width    : Integer := 0;
  index    : Integer := 0;
  x_index  : Integer := 0;
  y_index  : Integer := 0;
  maze     : Cell_matrix_50;
  soln_stk : Stack_of_coordinates;
  stk_top  : Coordinate  := (-1, -1);
  im_at    : Coordinate  := (0, 0);
  fin_at   : Coordinate  := (0, 0);
  can_go   : Can_go_next := ((-1,-1), (-1,-1), (-1,-1), (-1,-1));


-- MAIN --
begin

  -- get file name & open file stream for reading
  put("file name: ");
  get_line(filename, str_len);
  open(file, In_file, filename);

  -- parse file
  Parse: loop exit when End_of_file(file);
    
    get(file, width);
    get(file, height);
    
    Y_Loop: for y_index in 1..height loop
      exit when End_of_file(file);
      
      X_Loop: for x_index in 1..width loop
        exit when End_of_file(file);
        get(file, char);
        maze(x_index, y_index).piece := char;
        case char is
          when '.'    => maze(x_index, y_index).visited := false;
          when 'o'    => im_at  := (x_index, y_index);
                         maze(x_index, y_index).visited := true;
          when 'e'    => fin_at := (x_index, y_index);
                         maze(x_index, y_index).visited := false;
          when others => maze(x_index, y_index).visited := true;
        end case;
      end loop X_Loop;
    end loop Y_Loop;
  end loop Parse;
  close(file);

  clear(soln_stk);
  soln_stk(1) := im_at;

  -- implement DFS algorithm to find a solution for the maze
  Solve: loop
    stk_top := top(soln_stk);
    exit when stk_top = fin_at or stk_top = (-1, -1);
    
    where_can_i_go(stk_top, maze,width, height, can_go);
    
    if is_dead_end(can_go) then
      pop(soln_stk, stk_top);
    else
      for index in 1..4 loop
        if can_go(index) /= (-1, -1) then
          push(soln_stk, can_go(index));
          maze(can_go(index).x, can_go(index).y).visited := true;
          exit;
        end if;
      end loop;
    end if;
  end loop Solve;

  print_solution(soln_stk);

end a2; 
