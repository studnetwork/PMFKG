import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { JwtHelperService } from '@auth0/angular-jwt';
import { CookieService } from 'ngx-cookie-service';
import { Observable, of } from 'rxjs';
import { Jwt } from 'src/app/core/models/jwt.model';
import { environment } from 'src/environments/environment';


/**
 * Kreirano sa: `ng g s auth/services/auth`
 */
@Injectable({
  providedIn: 'root'
})
export class AuthService {

  private resourceUrl = `${environment.backendUrl}:${environment.backendPort}/auth`;

  private loginUrl = `${this.resourceUrl}/login`;
  private registerUrl = `${this.resourceUrl}/register`;

  constructor(
    private http: HttpClient, 
    private jwtHelper: JwtHelperService,
    private cookie: CookieService) { }

  login(email: string, password: string): Observable<Jwt> {
    return this.http.post<Jwt>(this.loginUrl, {email: email, password: password});
  }

  register(email: string, name: string, password: string): Observable<string> {

    return this.http.post(
      this.registerUrl, {
        email: email, 
        name: name, 
        password: password
      }, { 
        responseType: 'text'
      });
  }

  getToken(): string {
    return this.cookie.get("token");
  }

  saveToken(token: string): void {
    this.cookie.set("token", token);
  }

  deleteJwt(): void {
    this.cookie.delete("token");
  }

  isJwtValid(token: string): boolean {
    return ! this.jwtHelper.isTokenExpired(token);
  }

  isLoggedIn(): boolean {
    let isLoggedIn = this.cookie.check("token");
    console.log(`is logged in? ${isLoggedIn}`)
    return isLoggedIn;
  }
}
