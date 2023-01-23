import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Router } from '@angular/router';
import { JwtHelperService } from '@auth0/angular-jwt';
import { CookieService } from 'ngx-cookie-service';
import { Observable } from 'rxjs';
import { environment } from 'src/environments/environment';

@Injectable({
  providedIn: 'root'
})
export class AuthService {
  constructor(
    private cookieService: CookieService,
    private router: Router,
    private http: HttpClient,
    private jwtHelperService: JwtHelperService
  ) {}

  baseUrl = `${environment.backendUrl}/auth`;
  loginUrl = `${this.baseUrl}/login`;
  registerUrl = `${this.baseUrl}/register`;

  register(email: string, name: string, password: string): Observable<string> {
    let payload = {
      email: email,
      name: name,
      password: password
    };

    return this.http.post(this.registerUrl, payload, { responseType: 'text' });
  }

  login(email: string, password: string): Observable<string> {
    let payload = {
      email: email,
      password: password
    };

    return this.http.post(this.loginUrl, payload, { responseType: 'text' });
  }

  logout() {
    localStorage.removeItem('jwt');
    this.router.navigateByUrl('/login');
  }

  saveJwt(jwt: string): void {
    localStorage.setItem('jwt', jwt);
  }

  getJwt(): string | null {
    return localStorage.getItem('jwt');
  }

  isAuthenticated(): boolean {
    let jwt = this.getJwt();

    if(jwt == null) 
      return false;

    if(this.jwtHelperService.isTokenExpired(jwt))
      return false;

    return true;
  }
}
