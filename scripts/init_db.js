db_name = 'espotifai-db'
db = db.getSiblingDB(db_name)

//db.createRole(
//    {
//        role: 'espotifai-role',
//        privileges : [
//            {
//                resource :
//                {
//                    'db' : db_name,
//                    'collection': 'playlists'
//                },
//              actions: ['insert', 'remove', 'find', 'update']
//            },
//        ],
//        roles : []
//    }
//);
//
//db.createUser(
//    {
//        user: 'espotifai-user',
//        pwd: 'espotifai-pass',
//        roles: [
//            {
//                role: 'espotifai-role',
//                db: db_name,
//                collection: 'playlists'
//            },
//        ]
//    }
//);
