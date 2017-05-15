------------------------------------------
--       name:  Ben Turcotte            --
--         ID:  Bturcott                --
--          #:  0832217                 --
--      email:  bturcott@mail.guelph.ca --
-- assignment:  2                       --
--      class:  CIS*3190                --
------------------------------------------
-- Simple stack package.
-- Elements in the stack are Coordinate types
-- Intended use: a2.adb uses this package

package body stack is

  procedure clear(usr_stack : in out Stack_of_coordinates) is
    i : Integer := 0;
  begin
    for i in 1..5000 loop
      usr_stack(i) := (-1, -1);
    end loop;
  end clear;


  function size(usr_stack : in Stack_of_coordinates) return Integer is
    i : Integer := 1;
  begin
    loop
      exit when usr_stack(i) = (-1, -1);
      i := i +1;
    end loop;
    return i -1;
  end size;


  procedure push(usr_stack : in out Stack_of_coordinates; new_coord : in Coordinate) is
    i : Integer := 0;
  begin
    for i in 1..5000 loop
      if usr_stack(i) = (-1, -1) then
        usr_stack(i) := new_coord;
        exit;
      end if;
    end loop;
  end push;


  function top(usr_stack : in Stack_of_coordinates) return Coordinate is
    i      : Integer := 0;
    rtn_me : Coordinate := (-1, -1);
  begin
    for i in 1..4999 loop
      if usr_stack(i +1) = (-1, -1) then
        rtn_me := usr_stack(i);
        exit;
      end if;
    end loop;
    return rtn_me;
  end top;


  procedure pop(usr_stack : in out Stack_of_coordinates; popped : in out Coordinate) is
    i : Integer := 0;
  begin
    for i in 1..4999 loop
      if usr_stack(i +1) = (-1, -1) then
        popped := usr_stack(i);
        usr_stack(i) := (-1, -1);
        exit;
      end if;
    end loop;
  end pop;

end stack;