UPDATE currentusers
SET hallnum = :hallnum, cardnum = :cardnum, name = :name, isoff = :isoff
WHERE id = :id;
