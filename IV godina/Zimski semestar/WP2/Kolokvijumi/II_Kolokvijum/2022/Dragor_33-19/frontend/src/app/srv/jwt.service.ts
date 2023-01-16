import { Injectable } from '@angular/core';
import { JwtHelperService } from '@auth0/angular-jwt';

@Injectable({
  providedIn: 'root'
})
export class JwtService {

  constructor(
    private jwtHelper: JwtHelperService
  ) { }

  getJwt(): string | null {
    return localStorage.getItem('jwt')
  }

  setJwt(jwt: string) {
    localStorage.setItem('jwt', jwt)
  }

  deleteJwt() {
    localStorage.removeItem('jwt')
  }

  isJwtExpired(): boolean {
    return this.jwtHelper.isTokenExpired(this.getJwt())
  }

}
