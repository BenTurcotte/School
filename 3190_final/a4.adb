-- Bturcott - 832217
-- assignment 4 - CIS*3190
-- "Sieve of Atkin" - ada

with ada.text_io,  ada.integer_text_io, Ada.Task_Identification;
use  ada.text_io,  ada.integer_text_io, Ada.Task_Identification;
with ada.numerics, ada.text_io.text_streams;
use  ada.numerics, ada.text_io.text_streams;
with ada.numerics.generic_elementary_functions;
with ada.command_line;

procedure a4 is

  -- 
  package math_instance is new ada.numerics.generic_elementary_functions(Float);
  use math_instance;

  -- var declarations & (most of the) initialization
  fout        : File_Type;
  prime_flags : array (0..2000000) of Integer := (2|3 => 1, others => 0);
  lim_sqrt    : Float   := 0.0;
  lim         : Integer := 2000000;
  check_me    : Integer := 0;
  i           : Integer := 0;
  k           : Integer := 0;

begin

  -- prompt user for input
  Prompt_For_Limit: loop
    put("limit: ");
    get(lim);
    exit when lim > 0 and lim < 2000001;
    put("Error! Number must be between 0 and 200000.");
  end loop Prompt_For_Limit;



  -- init input-dependent var
  lim_sqrt := sqrt(Float(lim));

  -- do maths
  i := 1;
  i_loop: loop exit when i > integer(lim_sqrt);
    
    k := 1;
    k_loop: loop exit when k > integer(lim_sqrt);
      
      check_me := (4 * i * i) + (k * k);
      if check_me <= lim and check_me mod 12 in 1|5 then
        prime_flags(check_me) := 1;
      end if;
      
      check_me := (3 * i * i) + (k * k);
      if check_me <= lim and check_me mod 12 = 7 then
        prime_flags(check_me) := 1;
      end if;

      if i > k then
        check_me := (3 * i * i) - (k * k);
        if check_me <= lim and check_me mod 12 = 11 then
          prime_flags(check_me) := 1;
        end if;
      end if;
      
      k := k +1;
    end loop k_loop;
    
    i := i +1;
  end loop i_loop;

  -- eliminate multiples of primes
  rm_mult_loop: for i in 2..(lim -1) loop
    if prime_flags(i) = 1 then
      k := i * i;
      propagate_loop: loop exit when k >= lim or k < 0;
        prime_flags(k) := 0;
        k := k + i;
      end loop propagate_loop;
    end if;
  end loop rm_mult_loop;

  -- print results
  begin
    Create (File => fout, Mode => Out_File, Name => "ada_output.txt");
  exception
    when Name_Error|Status_Error|Use_Error =>
      put_line("Error: could not open output file.");
      ada.command_line.set_exit_status(1);
      abort_task(current_task);
  end;
  i := 0;
  print_loop: loop exit when i > lim;
    if prime_flags(i) = 1 then
      put(fout, i);
      put_line(fout, "");
    end if;
    i := i +1;
  end loop print_loop;
  close(fout);

  -- mic drop
end a4; 
