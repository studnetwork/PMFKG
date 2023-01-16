export interface User {
    _id: string;
    email: string;
    admin: boolean;
    hash: string;
    salt: string;
}
