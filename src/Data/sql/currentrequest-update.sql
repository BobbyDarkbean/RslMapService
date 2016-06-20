UPDATE currentrequests
SET userid = :userid, collection = :collection, rack = :rack, shelf = :shelf, position = :position,
    doctitle = :doctitle, doctype = :doctype, itemcount = :itemcount, status = :status
WHERE id = :id;
